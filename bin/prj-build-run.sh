#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd $curr_dir/../
n=""
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

make SHELL=/bin/bash OPT="$o" 1>/dev/null
if [ "$?" -eq "0" ]; then
	[ "$n" != "" ] && build/prj-out-"$o" "$n" || build/prj-out-"$o"
fi