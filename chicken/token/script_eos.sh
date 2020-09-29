#!/bin/bash

cleos -u http://eospush.tokenpocket.pro system buyram wd4rpecihuv5 chickentoken -k 200 -p wd4rpecihuv5@active

cleos -u http://eospush.tokenpocket.pro set account permission chickentoken \
 active '{"threshold":1,"keys":[{"key":"EOS5VmcpYPi9PwEmokMi6iizo9fnTBQZo9vXM9TpGitb2CCTCgcnw ","weight":1}],"accounts":[{"permission":{"actor":"chickentoken","permission":"eosio.code"},"weight":1}]}' \
 -p chickentoken@active

cleos -u http://eospush.tokenpocket.pro push action chickentoken create \
  '{"issuer":"chickenpools", "maximum_supply":"21000.0000 CHK"}' \
       -p chickentoken@active

cleos -u http://eospush.tokenpocket.pro push action chickentoken open \
 '{"owner":"chickentoken", "symbol":"4,CHK", "ram_payer":"chickentoken"}' \
 -p chickentoken

 cleos -u http://eospush.tokenpocket.pro set account permission gemtokencode owner permission.json -p gemtokencode@owner

 cleos -u http://eospush.tokenpocket.pro set account permission gemtokencode active \
'{"threshold":1,"keys":[],"accounts":[{"permission":{"actor":"gemtokencode","permission":"eosio.code"},"weight":1}]}' \
 -p gemtokencode@active