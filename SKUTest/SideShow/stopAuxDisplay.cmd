echo %1 
echo %2

if %1==Ultimate (goto startSimulator)

if %1==Professional (goto startSimulator)

if %1==Starter (EXIT)

if %2==Premium (goto startSimulator)

if %2==Basic (EXIT)

EXIT

:startSimulator

controlSimulator.exe 0 2
WaitForSimulator.exe 0 EXIT
windowssideshowvirtualdevice.exe /unregserver




