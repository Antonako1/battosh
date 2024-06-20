#!/bin/bash
set -e
cd "$(dirname "$0")"
if [ -f ../linux/shell/globals.sh ]; then
    . ../linux/shell/globals.sh
else
    echo "Error: globals.sh not found!"
    exit 1
fi
# cd "$(dirname "$0")"

# STANDALONE BUILDING
rm -rf ./output
BUILD_DIR="./output/linux"
mkdir -p "$BUILD_DIR"
../linux/shell/del.sh

../linux/build.sh "Release"
mkdir -p "$BUILD_DIR/docs"
cp -r ../docs/* "$BUILD_DIR/docs/"
mkdir -p "$BUILD_DIR/ATRC"
cp -r ../ATRC/* "$BUILD_DIR/ATRC/"
cp ../LICENSE "$BUILD_DIR/"
cp ../README.md "$BUILD_DIR/"
cp ../build/linux/$PROJECTNAME "$BUILD_DIR/"
cp ../extern_dependencies/ATRC/libs/linux/*.so "$BUILD_DIR/"
cd "$BUILD_DIR"
# zip -r "$PROJECTNAME-linux-standalone.zip" "$PROJECTNAME" docs ATRC LICENSE README.md *.so
tar -czvf "$PROJECTNAME-linux-standalone.tar.gz" "$PROJECTNAME" docs ATRC LICENSE README.md *.so

# APPIMAGE BUILDING
if [ ! -f ./appimagetool-x86_64.AppImage ]; then
        curl -LO https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage
        chmod 700 ./appimagetool-x86_64.AppImage
fi

ARCH=x86_64 ./appimagetool-x86_64.AppImage $PROJECTNAME.AppDir $PROJECTNAME-linux-x86_64.AppImage
