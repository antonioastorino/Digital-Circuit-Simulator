#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd $curr_dir/../
pwd
make OPT="$2"
if [ "$?" -eq "0" ]; then
	[ "$1" == "" ] && build/out-0 "$1" || build/out-"$2" "$1"
fi
popd