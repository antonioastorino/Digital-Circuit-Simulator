#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd $curr_dir/../
pwd
make $2
build/out-0 "$1"| tee gui/assets/test"$1".log
popd