#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
n="0"
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

./build-run.sh "$n" "$o" | tee ../gui/logic-analyzer/assets/test"-n$n-O$o".log
