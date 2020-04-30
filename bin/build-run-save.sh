#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd "$curr_dir"/
./build-run.sh "$1" "$2"
../build/out-"$2" "$1"| tee ../gui/logic-analyzer/assets/test"-n$1-O$2".log
popd