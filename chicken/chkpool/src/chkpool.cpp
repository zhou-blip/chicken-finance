#include <chkpool.hpp>

extern "C"
{
  void apply(uint64_t receiver, uint64_t code, uint64_t action)
  {
    if (code == receiver)
    {
      switch (action)
      {
        EOSIO_DISPATCH_HELPER(chkpool, (create)(claim)(harvest))
      }
    }
    else
    {
      if (action == name("transfer").value)
      {
        chkpool inst(name(receiver), name(code), datastream<const char *>(nullptr, 0));
        const auto t = unpack_action_data<transfer_args>();
        inst.handle_transfer(t.from, t.to, t.quantity, t.memo, name(code));
      }
    }
  }
}

void chkpool::create(name contract, symbol sym, asset reward, uint32_t epoch_time, uint32_t duration, asset min_staked)
{
  require_auth(ADMIN);

  pools_mi pools_tbl(_self, _self.value);
  auto itr = pools_tbl.begin();

  while (itr != pools_tbl.end())
  {
    auto exists = itr->contract == contract && itr->sym == sym;
    check(!exists, "Token exists");
    itr++;
  }

  check(reward.symbol == MINED_SYMBOL, "Reward symbol error");
  check(min_staked.symbol == sym, "Min staked symbol error");
  check(epoch_time > 0, "Invalid epoch");
  check(duration > 0, "Invalid duration");

  auto total = reward;
  itr = pools_tbl.begin();
  while (itr != pools_tbl.end())
  {
    total += itr->total_reward;
    itr++;
  }
  check(total.amount <= MAX_SUPPLY, "Reach the max circulation");

  auto pool_id = pools_tbl.available_primary_key();
  if (pool_id == 0)
    pool_id = 1;
  
  pools_tbl.emplace(_self, [&](auto &a) {
    a.id = pool_id;
    a.contract = contract;
    a.sym = sym;
    a.total_staked = asset(0, sym);
    a.total_reward = reward;
    a.released_reward = asset(0, reward.symbol);
    a.epoch_time = epoch_time;
    a.duration = duration;
    a.min_staked = min_staked;
    a.last_harvest_time = epoch_time;
  });
}

void chkpool::update(uint64_t pool_id, name contract, symbol sym, asset reward, uint32_t epoch_time, uint32_t duration, asset min_staked)
{
  require_auth(ADMIN);
  check(reward.symbol == MINED_SYMBOL, "Reward symbol error");

  pools_mi pools_tbl(_self, _self.value);
  auto p_itr = pools_tbl.require_find(pool_id, "Pool not exists");

  pools_tbl.modify(p_itr, same_payer, [&](auto &a) {
    a.contract = contract;
    a.sym = sym;
    a.total_reward = reward;
    a.epoch_time = epoch_time;
    a.duration = duration;
    a.min_staked = min_staked;
    a.last_harvest_time = epoch_time;
  });
}

void chkpool::claim(name owner, uint64_t pool_id)
{
  require_auth(owner);

  pools_mi pools_tbl(_self, _self.value);
  auto p_itr = pools_tbl.require_find(pool_id, "Pool not exists");
  miners_mi miners_tbl(_self, pool_id);
  auto m_itr = miners_tbl.require_find(owner.value, "No this miner");
  check(m_itr->unclaimed.amount > 0, "No unclaimed");

  auto quantity = m_itr->unclaimed;
  miners_tbl.modify(m_itr, same_payer, [&](auto &s) {
    s.claimed += quantity;
    s.unclaimed = asset(0, quantity.symbol);
  });

  utils::inline_transfer(MINED_CONTRACT, _self, owner, quantity, string("Minner claimed"));
}

void chkpool::harvest(uint64_t pool_id, uint32_t nonce)
{
  require_auth(ADMIN);

  pools_mi pools_tbl(_self, _self.value);
  auto itr = pools_tbl.require_find(pool_id, "Pool not exists");

  auto now_time = current_time_point().sec_since_epoch();
  check(now_time >= itr->epoch_time, "Mining hasn't started yet");
  check(now_time <= itr->epoch_time + itr->duration, "Mining is over");
  check(itr->total_staked.amount > 0, "No staked tokens");

  auto supply_per_second = safemath::div(itr->total_reward.amount, uint64_t(itr->duration));
  auto time_elapsed = now_time - itr->last_harvest_time;
  auto token_issued = asset(safemath::mul(uint64_t(time_elapsed), supply_per_second), itr->released_reward.symbol);
  pools_tbl.modify(itr, same_payer, [&](auto &s) {
    s.released_reward += token_issued;
    s.last_harvest_time = now_time;
  });

  // issue
  auto data = make_tuple(_self, token_issued, string("Issue Token"));
  action(permission_level{_self, "active"_n}, MINED_CONTRACT, "issue"_n, data).send();

  // update every miner
  miners_mi miners_tbl(_self, itr->id);
  auto m_itr = miners_tbl.begin();
  check(m_itr != miners_tbl.end(), "No miners");
  while (m_itr != miners_tbl.end()) {
    double radio = (double)(m_itr->staked.amount) / itr->total_staked.amount;
    uint64_t amount = (uint64_t)(token_issued.amount * radio);
    check(amount >= 0, "invalid amount");
    uint64_t unclaimed = safemath::add(m_itr->unclaimed.amount, amount);
    miners_tbl.modify(m_itr, same_payer, [&](auto &a) {
      a.unclaimed.amount = unclaimed;
    });
    m_itr++;
  }
}

void chkpool::handle_transfer(name from, name to, asset quantity, string memo, name code)
{
  if (from == _self || to != _self)
    return;
  
  require_auth(from);
  auto sym = quantity.symbol;
  pools_mi pools_tbl(_self, _self.value);
  auto itr = pools_tbl.begin();
  while (itr != pools_tbl.end()){
    if (itr->contract == code && itr->sym == sym)
      break;
    
    itr++;
  }

  check(itr != pools_tbl.end(), "Pool not found");
  check(itr->contract == code && itr->sym == sym, "Error token");
  check(quantity >= itr->min_staked, "The amount of staked is too small");
  auto now_time = current_time_point().sec_since_epoch();
  check(now_time >= itr->epoch_time, "Mining hasn't started yet");
  check(now_time <= itr->epoch_time + itr->duration, "Mining is over");

  const auto to_dev = asset(safemath::div(quantity.amount, uint64_t(10)), quantity.symbol); // 10% To Dev
  const auto to_stake = quantity - to_dev;    
                                                // 90% To Pool
  utils::inline_transfer(code, _self, from, to_stake, string("refund"));
  utils::inline_transfer(code, _self, DEV_FUNDS, to_dev, string("Dev Rewards"));

  pools_tbl.modify(itr, same_payer, [&](auto &s) {
    s.total_staked += to_stake;
  });

  miners_mi miners_tbl(_self, itr->id);
  auto m_itr = miners_tbl.find(from.value);
  if (m_itr == miners_tbl.end())
  {
    auto zero = asset(0, MINED_SYMBOL);
    miners_tbl.emplace(_self, [&](auto &a) {
      a.owner = from;
      a.staked = to_stake;
      a.claimed = zero;
      a.unclaimed = zero;
    });
  }
  else
  {
    miners_tbl.modify(m_itr, same_payer, [&](auto &a) {
      a.staked += to_stake;
    });
  }
}
