IF %2 == "" (
    echo Executing Build Action 0
    C:
    CD
    echo Changing the currently being built root directory to %1
    cd %1
    build -cPbmeEowvyZPi$ /x86 /why *
    exit
) else (
    echo Executing Build Action 1
    C:
    CD
    echo Building specified directory of %2.
    cd %2
    build -cPbmeEowvyZPi$ /x86 /why /r %2 *
    exit
)