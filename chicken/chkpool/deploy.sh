#!/bin/bash

rm -rf *.abi*
rm -rf *.wasm*

eosio-cpp -abigen -I include -R resource -contract chkpool -o chkpool.wasm src/chkpool.cpp

cleos -u http://eospush.tokenpocket.pro set contract chickenpools $(pwd)
