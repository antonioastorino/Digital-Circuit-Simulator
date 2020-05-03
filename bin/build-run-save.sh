#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
if [ "$2" == "" ]; then
	./build-run.sh "$1 0" | tee ../gui/logic-analyzer/assets/test"-n$1-O0".log
	echo
	echo
else
	./build-run.sh "$1 $2" | tee ../gui/logic-analyzer/assets/test"-n$1-O$2".log
fi