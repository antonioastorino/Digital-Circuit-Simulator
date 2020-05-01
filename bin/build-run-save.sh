#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
./build-run.sh "$1" "$2" | tee ../gui/logic-analyzer/assets/test"-n$1-O$2".log