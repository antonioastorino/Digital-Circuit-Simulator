#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd $curr_dir/../
pwd
make clean;
cd bin
./build-run-save.sh "$1" "$2"
popd