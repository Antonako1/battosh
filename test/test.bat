if "A" == "A" echo test

if exist data (
    if not exist "ququ" (
        echo w
    ) else if "A" == "A" (
        echo e
    ) else (
        echo q
    )
) else if exist "haha" (
    echo Hi from the other side
) else (
    echo data exists
)

if "A" == "A" echo test
