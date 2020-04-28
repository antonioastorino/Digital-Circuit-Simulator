#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd $curr_dir/../
pwd
make $1
build/out-0
popd