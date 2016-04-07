set SKUDOMAIN=REDMOND
set SKUUSER=igloolab
set SKUPASS=Jan-11polaris

echo set LLU_Default; the user that WTT accesses the network as.
"%programfiles%\WTT 2.2\Client\wttcmd.exe" /addlogicaluser /localname:LLU_NAO /user:%SKUUSER% /domain:%SKUDOMAIN% /password:%SKUPASS%
"%programfiles%\WTT 2.2\Client\wttcmd.exe" /addlogicaluser /localname:LLU_Default /user:%SKUUSER% /domain:%SKUDOMAIN% /password:%SKUPASS%