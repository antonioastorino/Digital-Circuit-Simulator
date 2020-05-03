#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd $curr_dir/../
make OPT="$2" 1>/dev/null
if [ "$?" -eq "0" ]; then
	if [ "$2" == "" ]; then
		build/out-0 "$1"
	else
		build/out-"$2" "$1"
	fi
fi