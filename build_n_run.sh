#!/bin/bash
cd "$(dirname "$0")"
cd linux
./build.sh
./run.sh "$@"