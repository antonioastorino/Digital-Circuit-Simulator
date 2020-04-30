#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
pushd $curr_dir/../
pwd
make OPT="$2"
[ "$1" == "" ] && build/out-0 "$1" || build/out-"$2" "$1"
popd