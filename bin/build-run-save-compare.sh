#!/bin/zsh
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
n="0"
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

./build-run.sh "$n" "$o" | tee ../debug/new"-n$n-O$o".log
if [ "$?" -eq 0 ]; then
	echo "Checking..."
	DIFF=`diff ../debug/new"-n$n-O$o".log ../gui/logic-analyzer/assets/test"-n$n-O$o".log`
	if [ "$DIFF" != "" ]; then
		echo "Error: test not passed"
		print "$DIFF"
	else
		echo "Test passed"
	fi
fi

