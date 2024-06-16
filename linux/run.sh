#!/bin/sh
echo "Running project..."
cd "$(dirname "$0")"
. ./shell/globals.sh
cd ../build
./"$PROJECTNAME" "$@"
cd ..