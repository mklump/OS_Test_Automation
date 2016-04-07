set /p MACHINENAME="Please enter machine name: -> "
set /p IGLOOLABPASSWORD="Please enter test account REDMOND\igloolab password: -> "

asi.exe -install -MACHINENAME %MACHINENAME% -WTTCD -SKU ENTERPRISE -LANGUAGE EN-US -PLATFORM amd64 -QUALITY TEST -LAB MAIN -PRODUCT VISTA -TYPE FRE -AUTOLOGON Administrator -USER Administrator "" Administrators -DISPLAY 1024 768 32 72 -JOINDOMAIN igloolab REDMOND %IGLOOLABPASSWORD% -FORMATDISK D: -INSTALLTO D: -SWAPACTIVE D: -WTTINSTALLCLIENT -WTTCONTROLLER B11BGITWTTCT25 -DISKPART "Select disk 0, clean, create partition primary size=60000, assign letter=C, create partition primary size=40000, assign letter=D, create partition primary, assign letter=E, exit" -POSTINSTALL \\wexfs\USERS\a-maklum\edrive\OSPostInstall.cmd