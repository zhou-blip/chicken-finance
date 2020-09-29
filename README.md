# chicken-finance

## Introduction
CHK is is the yield farming on EOS. The private key is burned and the contract code is open source.
The project has no pre-mine, no founder shares, no VC interests. CHK uses TVI (Total Value Inflow) as the project.
The token distribution index will not cause precipitation in the fund pool. The contract will automatically return
90% of the funds to the participating EOS accounts and donate 10% as follow-up development and operation funds.

## Token Info

- Token name: Chicken（CHK）
- Total supply: 21000.0000
- Token contract: [chickentoken](https://bloks.io/account/chickentoken)
- Pool contract: [chickenpools](https://bloks.io/account/chickenpools)
- Chicken Pool:
1. EOS: 13000 CHK
2. USDT: 2000 CHK
3. USN: 1100 CHK
4. DFS: 1100 CHK
5. BOX: 1100 CHK
6. ...

CHK will be distributed in only three weeks.

## Reasons for token selection
- Stable coins issued based on the EOS network (USDT, USN)
- DEX (DFS, BOX) developed based on EOS network

## Security

### No pool of funds
CHK uses the TVI model as a project value assessment, and will not lock any funds in the contract, so it can ensure the 100% security of the contract.

### Private keys burned
RAB has given the authority to the system account `eosio`, the project has no control and cannot update the contract (unless the 21 BPs agree).

### How to verify the contract

- EOSIO Version: 2.0.5
- EOS.CDT Version: 1.7.0

```
cleos get code chickentoken > chickentoken.hash
cleos get code chickenpools > chickenpools.hash
```

Build from source:
```
cd chicken/chkpool
./build.sh

cd chicken/token
./build.sh
```

Compare the hash:  
`shasum -a 256 chicken/chkpool/chkpool.wasm` of `chickenpools.hash`  
`shasum -a 256 chicken/token/token.wasm` of `chickentoken.hash`

- Pool Hash: 31e95c85718b798454fb2c1f3ff5dd97caa8bfd78f05132ecead416cc868604d
- Token Hash: a9dffc7588044ddab590f70ddb777bef50280eb36db491fc8601a0f6b5b67f83
