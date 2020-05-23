#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd $curr_dir/../
n="0"
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

make OPT="$o" 1>/dev/null
if [ "$?" -eq "0" ]; then
	build/prj-out-"$o" "$n"
fi