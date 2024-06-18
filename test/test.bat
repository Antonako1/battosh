@echo off
if exist data (
    if not exist "ququ" (
        echo w
    ) else (
        echo q
    )
) else if exist "haha" (
    echo Hi from the other side
) else (
    echo data exists
)


ver
cls
call haha
type test.txt
:: TEST
echo Hi
cd "C:\temp"
exit /B 10

cmake --build . --target test

if not exist data (
    echo data does not exist
) else (
    echo data exists
)

if "A" == "A" echo test
