#!/bin/bash

rm -rf *.abi*
rm -rf *.wasm*

eosio-cpp -abigen -I include -R resource -contract chkpool -o chkpool.wasm src/chkpool.cpp
