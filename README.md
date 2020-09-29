# chicken-finance

## 说明
CHK是EOS上的流动性挖矿项目，私钥已经多签给著名钱包和超级节点，并且合约已经开源，项目没有预挖，没有私募，没有VC投资。
CHK是使用TVI(Total Value Inflow)模式的项目, 不需要质押资金池，合约将自动返回90%的资金投入参与EOS账户，并捐赠10%作为后续开发运营资金。

## 代币信息

- 代码名称: Chicken（CHK）
- 发行总量: 21000.0000
- 代币合约: [chickentoken](https://bloks.io/account/chickentoken)
- 矿池合约: [chickenpools](https://bloks.io/account/chickenpools)
- 养鸡矿池:
1. EOS: 13000 CHK
2. USDT: 2000 CHK
3. USN: 1100 CHK
4. DFS: 1100 CHK
5. BOX: 1100 CHK
6. 待定: 2700 CHK

CHK每个矿池将在3周(21天)时间挖完

## 安全性

### 没有质押资金池
CHK 使用TVI模式分发，没有质押资金池，所以能确保合约的100%安全性。

### 私钥多签
CHK 没有私钥，通过与著名钱包和节点进行多签, 项目方将无法独自修改合约内容。

### 如何验证合约

- EOSIO 版本: 2.0.5
- EOS.CDT 版本: 1.7.0

```
# 获取部署的合约hash值
cleos get code chickentoken > chickentoken.hash
cleos get code chickenpools > chickenpools.hash
```

编译源码:
```
cd chicken/chkpool
./build.sh

cd chicken/token
./build.sh
```

获取源码编译文件的hash值，对比与部署的合约hash值是否一致:  
`shasum -a 256 chicken/chkpool/chkpool.wasm` of `chickenpools.hash`  
`shasum -a 256 chicken/token/token.wasm` of `chickentoken.hash`

- 矿池合约 Hash: 31e95c85718b798454fb2c1f3ff5dd97caa8bfd78f05132ecead416cc868604d
- 代币合约 Hash: a9dffc7588044ddab590f70ddb777bef50280eb36db491fc8601a0f6b5b67f83


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
CHK has given the authority to the system account `eosio`, the project has no control and cannot update the contract (unless the 21 BPs agree).

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

