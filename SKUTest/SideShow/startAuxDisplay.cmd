echo %1 
echo %2

if %1==Ultimate (goto startSimulator)

if %1==Professional (goto startSimulator)

if %1==Starter (EXIT)

if %2==Premium (goto startSimulator)

if %2==Basic (EXIT)

EXIT

:startSimulator
windowssideshowvirtualdevice.exe /regserver
start virtualsideshow.exe 0 Uninstall
WaitForSimulator.exe 0



