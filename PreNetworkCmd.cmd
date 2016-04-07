

REM This file will be executed post network initialization when the ODE CD boots.

REM    To run Ode Setup Wizard instead of ASIUI, comment out the ASIUI.exe above and 
REM    enable the call to OdeSetup.exe below.
REM    Syntax
REM          OdeSetup.exe <Param1=Value1> <Param2=Value2> ...
REM
REM    Where the Parameters could be one of the following.
REM
REM       MachineName       Name to use for the machine. Use ‘*’ to auto generate machine name.
REM
REM       TimeServer        The time server to use to sync to. (default is no time server).
REM
REM       TimeZone          The time zone to associate the machine to. Use the standard name of the time zone. E.g. ‘Pacific Standard Time’. 
REM
REM       EnableFirewall    Whether or not to turn the firewall on. Set to True/False. (default is false).
REM
REM       PromptUser        Whether or not to show the Ode Setup screens leading up to the Ode installation. Set to True/False. 
REM                         Setting it to False will directly start the installation of the Ode without giving the user the chance to modify the incoming settings. (default is true).
REM                         Please note that if ‘PromptUser’ is set to False, and validation for any of the fields fails, the user will be prompted to provide a valid input.
REM
REM
REM       OdePolicyRoot     Policy root to use for the Ode installation. Default is 'OdeHdd'.
REM
REM       Reboot            Whether or not to reboot the machine after OdeSetup.exe finishes. Set to True/False. (default is true).
REM
REM       Partitions        List of partition information specifying  diskid, size, alias and OdeType.
REM
REM                         Each partition is specified as diskId, size, alias [,OdeType]
REM                             DiskId  – disk Id of the disk to create the partition on.
REM                             Size    – size in MB of the partition.
REM                             Alias   – alias to use for the partition.
REM                             OdeType – arch of the Ode installation. Can be one of
REM                                       x86     – install x86 ode
REM                                       amd64   – install amd64 ode
REM                                       ia64    – install ia64 ode
REM                                       default – install ode based on the type of the ode the wizard is running on.                       
REM                                       If not specified, Ode will not be installed on that partition.
REM
REM                             This parameter is list of partition information separated by ‘;’
REM 
REM                             e.g.  0,2000,Ode,x86 ;  0,10000,TestOS
REM                             (On Disk 0, create the first partition with alias ‘Ode’ of size 2000MB and install the x86 Ode, create the second partition of size 10000MB with alias ‘TestOS’ without any Ode on it.)

set /p MACHINENAME="Please enter machine name: -> "
set /p IGLOOLAB_PASSWORD="Please enter REDMOND\igloolab password: -> "
set asi_originalpath=%IGLOOLAB_PASSWORD%

echo
echo Register ASI 3.0 WTT client
echo
asicmd.exe register /server B11BGITWTTCT25 /user REDMOND\igloolab /password %IGLOOLAB_PASSWORD%

echo Configure disk partitions
diskpart /s diskreconfig.script

echo Execute ASICMD.exe asi command interpreter
asicmd.exe /script WTTCD3.0.script

echo Uncomment/Comment the following line out to enable/disable running ASIUI.exe
REM AsiUI.exe
