#!/bin/bash

# gempoolscode

cleos -u http://eospush.tokenpocket.pro system buyram wd4rpecihuv5 chickenpools -k 200 -p wd4rpecihuv5@active

cleos -u http://eospush.tokenpocket.pro set account permission chickenpools active \
'{"threshold":1,"keys":[{"key":"EOS5VmcpYPi9PwEmokMi6iizo9fnTBQZo9vXM9TpGitb2CCTCgcnw","weight":1}],"accounts":[{"permission":{"actor":"chickenpools","permission":"eosio.code"},"weight":1}]}' \
 -p chickenpools@active

cleos -u http://eospush.tokenpocket.pro push action chickenpools create '["eosio.token","4,EOS","13000.0000 CHK",1600574400,1209600,"1.0000 EOS"]' -p chickenadmin
cleos -u http://eospush.tokenpocket.pro push action chickenpools create '["tethertether","4,USDT","2000.0000 CHK",1600574400,1209600,"3.0000 USDT"]' -p chickenadmin
cleos -u http://eospush.tokenpocket.pro push action chickenpools create '["eosdtsttoken","9,EOSDT","2000.0000 CHK",1600574400,1209600,"3.000000000 EOSDT"]' -p chickenadmin
cleos -u http://eospush.tokenpocket.pro push action chickenpools create '["usdetotokens","4,USDE","2000.0000 CHK",1600574400,1209600,"3.0000 USDE"]' -p chickenadmin
cleos -u http://eospush.tokenpocket.pro push action chickenpools create '["danchortoken","4,USN","2000.0000 CHK",1600574400,1209600,"3.0000 USN"]' -p chickenadmin

cleos -u http://eospush.tokenpocket.pro get table chickenpools chickenpools pools
cleos -u http://eospush.tokenpocket.pro get table chickenpools 1 miners
cleos -u http://eospush.tokenpocket.pro push action chickenpools harvest '[1,5]' -p chickenadmin
cleos -u http://eospush.tokenpocket.pro push action chickenpools harvest2 '[2,5]' -p chickenadmin


