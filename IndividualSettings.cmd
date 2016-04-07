setlocal enabledelayedexpansion

set Language1=ENGLISH
set Language2=GERMAN
set Language3=JAPANESE
set Language4=ARABIC
set Language5=PSEUDO-LOCALIZED
set Language6=PS-MI
REM	MIRRORED_PSEUDOLOC

set Edition1=Starter
set Edition2=Home
set Edition3=Home_Premium
set Edition4=Business
set Edition5=Pro_Enterprise
set Edition6=Ultimate

set Platform1=x86
set Platform2=amd64

set TRUECOMPUTERNAME=%COMPUTERNAME:_S=%

echo Register test machine with ASI3.0 controller B11BGITWTTCT25
asicmd.exe unregister
asicmd.exe register /server B11BGITWTTCT25 /user REDMOND\igloolab /password Jan-11polaris

echo Set the install remainder for the command
rem FBL_SHELL_DEV1
set COMMANDREMAINDER=os:WIN7 type:chk buildnumber:6965 lab:WINMAIN_WIN7BETA /osconfig machinename:[Current] adduser:LocalAdmin,Administrators,Admin-1 Autologon:LocalAdmin adduser:Administrator,Administrators,Admin#1 adduser:LocalProtectedA,Administrators,Admin-1 adduser:LocalStandardUser,Users adduser:WEXTester,Users oobe:true asisetup:true display:1024,768,32,72 remotedesktop:true /diskconfig format:C:,NTFS,Test_OS installto:C: bootfrom:D: /verbose /runfrom d:

echo Install latest WIN7 FBL_SHELL_DEV1 build based on test mix setup...
if !TRUECOMPUTERNAME!==DEPLAB02 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB04 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB05 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB06 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB07 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB08 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB09 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB10 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB11 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB12 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform1! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB13 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB14 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB15 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB16 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB17 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB18 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB19 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB20 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform1! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB21 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB22 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB23 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB24 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB25 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB26 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB27 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB28 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB29 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB30 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB31 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB32 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform1! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB33 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB34 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB35 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB36 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB37 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB38 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB39 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB40 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DEPLAB41 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB42 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB43 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DEPLAB44 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition1! architecture:!Platform1! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==DUALSOCK1 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DUALSOCK2 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==DUALSOCK3 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform2! %COMMANDREMAINDER%)

if !TRUECOMPUTERNAME!==B10-04 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition2! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==B10-05 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition3! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==B10-06 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition4! architecture:!Platform2! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==B10-07 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition5! architecture:!Platform1! %COMMANDREMAINDER%)
if !TRUECOMPUTERNAME!==B10-08 (asicmd.exe install /OSAttribute language:!Language1! edition:!Edition6! architecture:!Platform1! %COMMANDREMAINDER%)

endlocal