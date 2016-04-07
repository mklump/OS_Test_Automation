set RAZZLEROOT=C:\ENLIST\Win7SCSETest\tools
set BUILDROOT=C:\ENLIST\Win7SCSETest\testsrc\shelltest\testareas\SKUTest
start /B /NORMAL /WAIT CALL %RAZZLEROOT%\razzle.cmd amd64 no_oacr exec CALL "%BUILDROOT%\buildSKUTest(s)_x64.cmd" "%BUILDROOT%" "%1"