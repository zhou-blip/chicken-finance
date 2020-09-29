#include <structs.hpp>

namespace utils
{
  void inline_transfer(const name &contract, const name &from, const name &to, const asset &quantity, const string &memo)
  {
    auto data = make_tuple(from, to, quantity, memo);
    action(permission_level{from, "active"_n}, contract, "transfer"_n, data).send();
  }

  void buyram(const name &payer, const name &receiver, const asset &quant)
  {
    auto data = make_tuple(payer, receiver, quant);
    action(permission_level{payer, "active"_n}, "eosio"_n, "buyram"_n, data).send();
  }

} // namespace utils