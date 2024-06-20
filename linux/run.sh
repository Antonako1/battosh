#!/bin/sh
echo "Running project..."
cd "$(dirname "$0")"
. ./shell/globals.sh
cd ../build

cp ../test/test.bat ./linux/test.bat
cp ../extern_dependencies/ATRC/libs/linux/* ./linux/

# ATRC_PATH="/home/$USER/battosh/ATRC"
# if [ ! -d "$ATRC_PATH" ]; then
#     mkdir -p "$ATRC_PATH"
# fi

# cp -r ../ATRC/* "$ATRC_PATH"

cp ../test/test.bat ./linux/test.bat

./linux/"$PROJECTNAME" "$@"
echo $?
cp ./linux/*.sh ../test
cd ..


# copy /Y ..\test\test.bat .\win\test.bat
# copy /B /Y ..\extern_dependencies\ATRC\libs\win\* .\win\

# set "ATRC_PATH=C:\Users\%USERNAME%\battosh\ATRC"
# if not exist %ATRC_PATH% mkdir %ATRC_PATH%
# copy /Y ..\ATRC\* %ATRC_PATH%
# echo.
# echo.
# .\win\%PROJECTNAME%.exe %*
# echo %ERRORLEVEL%
# copy /Y .\win\*.sh ..\test
# cd ..