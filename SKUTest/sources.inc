TEST_CODE=1

TARGETTYPE=DYNLINK

DLLENTRY=_DllMainCRTStartup

MUI=0
LANGUAGE_NEUTRAL=0

USE_MSVCRT=1
USE_STATIC_ATL=1
ATL_VER=70
USE_VCCOM=1
USE_NATIVE_EH=1


INCLUDES  =      $(SHELL_TST_ROOT)\testareas\SKUtest\inc; \
                 $(SHELL_TST_ROOT)\testareas\SKUtest; \
		 $(SHELL_INC_PATH); \
                 $(SHELL_TST_INC_PATH); \
                 $(PROJECT_OBJ_ROOT)\tools\xacc\xacc\$(O); \
                 $(PROJECT_OBJ_ROOT)\tools\xacc\xaccconstants\$(O); \
                 $(PROJECT_OBJ_ROOT)\tools\xacc\xaccshell\$O; \
                 $(PROJECT_OBJ_ROOT)\tools\shtestex\$O; \

TARGETLIBS =    $(SDK_LIB_PATH)\kernel32.lib                       \
                $(SDK_LIB_PATH)\comctl32.lib                       \
                $(SDK_LIB_PATH)\user32.lib                         \
                $(SDK_LIB_PATH)\shell32.lib                       \
                $(SDK_LIB_PATH)\ole32.lib                          \
                $(SDK_LIB_PATH)\oleaut32.lib                       \
                $(SDK_LIB_PATH)\shlwapi.lib                       \
                $(SDK_LIB_PATH)\netapi32.lib        \
                $(PROJECT_OBJ_ROOT)\tools\harnesses\mash2\MashLib\$O\MashLib.lib \
                $(PROJECT_OBJ_ROOT)\testareas\SKUtest\lib\$O\SKUDiff_UTIL.lib \
                $(SHELL_TST_LIB_PATH)\AutomationObjectsInit.lib               \
				

