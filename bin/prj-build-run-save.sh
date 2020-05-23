#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
n="0"
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

filename="../gui/logic-analyzer/assets/prj-"-n$n-O$o".log"

./prj-build-run.sh "$n" "$o" | tee $filename
if ! [ -s $filename ]; then
	rm $filename
fi

