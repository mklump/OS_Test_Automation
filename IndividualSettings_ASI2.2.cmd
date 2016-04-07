setlocal enabledelayedexpansion

set Language1=ENGLISH
set Language2=GERMAN
set Language3=JAPANESE
set Language4=ARABIC
set Language5=PSEUDO-LOCALIZED
set Language6=MIRRORED_PSEUDOLOC

set Edition1=Starter
set Edition2=Home
set Edition3=Home_Premium
set Edition4=PROFESSIONAL
set Edition5=Pro_Enterprise
set Edition6=Ultimate

set Platform1=x86
set Platform2=amd64

set TRUECOMPUTERNAME=%COMPUTERNAME:_S=%

asi.exe -QUIET -REGISTER -PRODUCT WIN7 -LAB FBL_SHELL_DEV1 -TYPE FRE -MACHINENAME [Current_no_s] -USER Tester Admin#1 Administrators -AUTOLOGON Tester -USER Administrator Admin#1 Administrators -REMOTEDESKTOP -DISPLAY 1024 768 32 72 -FORMATDISK C: -INSTALLTO C: -ADDDRIVER E:\Drivers

if !TRUECOMPUTERNAME!==DEPLAB13 (asi.exe -QUIET -register -LANGUAGE !Language6! -SKU !Edition4! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB14 (asi.exe -QUIET -register -LANGUAGE !Language6! -SKU !Edition6! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB15 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition5! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB16 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition4! -Platform !Platform1!)

if !TRUECOMPUTERNAME!==DEPLAB17 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition5! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB18 (asi.exe -QUIET -register -LANGUAGE !Language4! -SKU !Edition3! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB19 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition1! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB20 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition6! -Platform !Platform2!)

if !TRUECOMPUTERNAME!==DEPLAB21 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition4! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB22 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition4! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB23 (asi.exe -QUIET -register -LANGUAGE !Language2! -SKU !Edition5! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB24 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition5! -Platform !Platform2!)

if !TRUECOMPUTERNAME!==DEPLAB25 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition2! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB26 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition2! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB27 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition3! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB28 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition3! -Platform !Platform1!)

if !TRUECOMPUTERNAME!==DEPLAB29 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition1! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB30 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition1! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB31 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition6! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB32 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition6! -Platform !Platform1!)

if !TRUECOMPUTERNAME!==DEPLAB33 (asi.exe -QUIET -register -LANGUAGE !Language4! -SKU !Edition3! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB34 (asi.exe -QUIET -register -LANGUAGE !Language2! -SKU !Edition1! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB35 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition1! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB36 (asi.exe -QUIET -register -LANGUAGE !Language3! -SKU !Edition1! -Platform !Platform1!)

if !TRUECOMPUTERNAME!==DEPLAB37 (asi.exe -QUIET -register -LANGUAGE !Language4! -SKU !Edition1! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB38 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition6! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB39 (asi.exe -QUIET -register -LANGUAGE !Language5! -SKU !Edition6! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB40 (asi.exe -QUIET -register -LANGUAGE !Language4! -SKU !Edition6! -Platform !Platform2!)

if !TRUECOMPUTERNAME!==DEPLAB41 (asi.exe -QUIET -register -LANGUAGE !Language2! -SKU !Edition5! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB42 (asi.exe -QUIET -register -LANGUAGE !Language4! -SKU !Edition5! -Platform !Platform1!)
if !TRUECOMPUTERNAME!==DEPLAB43 (asi.exe -QUIET -register -LANGUAGE !Language1! -SKU !Edition5! -Platform !Platform2!)
if !TRUECOMPUTERNAME!==DEPLAB44 (asi.exe -QUIET -register -LANGUAGE !Language3! -SKU !Edition5! -Platform !Platform1!)

endlocal