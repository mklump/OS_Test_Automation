echo Install ApVerify... new untested.
net use j: \\ae-share\tools /user:%SKUDOMAIN%\%SKUUSER% %SKUPASS%
call j:\release\AppVerifier\latest\avrfinstall.cmd
net use j: /delete

echo Install the debugger
net use j: \\dbg\privates /user:%SKUDOMAIN%\%SKUUSER% %SKUPASS%
call j:\latest\dbginstall.cmd
net use j: /delete
c:\debuggers\windbg -IS

echo Install WTT client from %WTTCONTROLLER%
net use j: \\%WTTCONTROLLER%\wttinstall\client /user:%SKUDOMAIN%\%SKUUSER% %SKUPASS%
j:\setup.exe /uninstall
j:\setup.exe /qb ICFAGREE="Yes"
REM DRIVESELECTION="E:\"
net use j: /delete

echo set LLU_Default; the user that WTT accesses the network as.
"%programfiles%\WTT 2.2\Client\wttcmd.exe" /addlogicaluser /localname:LLU_NAO /user:%SKUUSER% /domain:%SKUDOMAIN% /password:%SKUPASS%
"%programfiles%\WTT 2.2\Client\wttcmd.exe" /addlogicaluser /localname:LLU_Default /user:%SKUUSER% /domain:%SKUDOMAIN% /password:%SKUPASS%

echo Turn off hibernation
powercfg -s SCHEME_MIN

echo restart the WTT service so changes take effect
net stop wttsvc
net start wttsvc

REM echo set TESTBINROOT; the path where test files are copied from
REM "%programfiles%\WTT 2.2\Client\wttcmd.exe" /configreg /add /value:WTT\TestBinRoot /data:%TESTBINROOT%

echo Register test client with ASI2.2
asi.exe -register AUTHENTICATE

echo Register test client with ASI3.0
asicmd.exe register /server %WTTCONTROLLER% /user %SKUDOMAIN%\%SKUUSER% /password %SKUPASS% 
