set SKUDOMAIN=REDMOND
set SKUUSER=igloolab
set SKUPASS=Jan-11polaris
set WTTCONTROLLER=B11BGITWTTCT25

if %SystemDrive%==C: (goto testos)
if %SystemDrive%==D: (goto safeos)

:testos
REM echo Install WTT client from %WTTCONTROLLER%
REM net use j: \\%WTTCONTROLLER%\wttinstall\client /user:%SKUDOMAIN%\%SKUUSER% %SKUPASS%
REM j:\setup.exe /qb ICFAGREE="Yes"
REM net use j: /delete

powercfg -s SCHEME_MIN
bcdedit /export e:\testosbcd
bcdedit /export d:\safeosbcd 

REM ECHO Change OSBinRoot Settings to %1 for x86 machines.
REM ECHO Change TestBinRoot Settings to %3 for x86 machines.
REM if %processor_architecture%==x86 
REM ( 
REM 	"%programfiles%\WTT 2.2\Client\wttcmd.exe" /configreg /add /value:WTT\OsBinRoot /data:%1
REM 	"%programfiles%\WTT 2.2\Client\wttcmd.exe" /configreg /add /value:WTT\TestBinRoot /data:%3
REM )

REM ECHO Change WoW64OsBinRoot Settings to %2 for amd64 machines.
REM ECHO Change WoW64TestBinRoot Settings to %4 for amd64 machines.
REM if %processor_architecture%==AMD64
REM (
REM 	"%programfiles%\WTT 2.2\Client\wttcmd.exe" /configreg /add /value:WTT\WoW64OsBinRoot /data:%2
REM 	"%programfiles%\WTT 2.2\Client\wttcmd.exe" /configreg /add /value:WTT\WoW64TestBinRoot /data:%4
REM )

REM sc stop wttsvc && sc start wttsvc
exit

:safeos
bcdedit /export e:\safeosbcd 
bcdedit /export d:\safeosbcd 
exit
