#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd $curr_dir/../
pwd
make clean; make
build/out-0
popd