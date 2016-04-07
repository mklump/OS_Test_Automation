set /p MACHINENAME="Please enter machine name: -> "
set /p IGLOOLABPASSWORD="Please enter test account REDMOND\igloolab password: -> "

echo Register test machine with ASI3.0 controller 
asicmd.exe unregister
asicmd.exe register /server /user REDMOND\igloolab /password %IGLOOLABPASSWORD%

echo Install Vista SafeOS...
asicmd.exe install /osconfig machinename:%MACHINENAME% asisetup:true display:1024,768,32,72 autologon:Administrator adduser:Administrator,Administrators joindomain:REDMOND,igloolab,%IGLOOLABPASSWORD% /OSAttribute edition:ENTERPRISE language:EN-US architecture:amd64 os:VISTA servicepack:2 type:FRE /diskconfig format:C:,NTFS,Test_OS format:D:,NTFS,WTTRESERVED format:E:,NTFS,UTILITY installto:D: bootfrom:D: partition:0,40000,C:,Test_OS partition:0,30000,D:,WTTRESERVED partition:0,*,E:,UTILITY /runcommand postinstall:\\wexfs\USERS\a-maklum\edrive\OSPostInstall.cmd /verbose