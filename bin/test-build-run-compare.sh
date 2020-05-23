#!/bin/zsh
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
n="0"
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"
out_file=../debug/test"-n$n-O$o".log

./test-build-run.sh "$n" "$o" > $out_file
if [ "$?" -eq 0 ]; then
	DIFF=`diff $out_file ../gui/logic-analyzer/assets/test-n$n-O0.log` &&
	echo "Checking..." &&
	if [ "$DIFF" != "" ]; then
		echo "Error: test $n not passed"
		cat $out_file
		print "$DIFF"
	else
		echo "Test $n passed"
		rm $out_file
	fi
fi

