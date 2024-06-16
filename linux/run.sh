#!/bin/sh
echo "Running project..."
cd "$(dirname "$0")"
. ./shell/globals.sh
cd ../build
./linux/"$PROJECTNAME" "$@"
cd ..