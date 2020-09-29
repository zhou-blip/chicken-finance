#!/bin/bash

rm -rf *.abi*
rm -rf *.wasm*

eosio-cpp -abigen -I include -R resource -contract token -o token.wasm src/token.cpp

cleos -u http://eospush.tokenpocket.pro set contract chickentoken $(pwd)
