#!/bin/zsh
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
o="0"
if [ "$1" -eq "" ]; then
	echo "ERROR: please specify the test number"
	exit 1
else 
	n="$1"
fi
[ "$2" != "" ] && o="$2"
[ ! -d ../debug ] && mkdir ../debug
out_file=../debug/test"-n$n".log

./test-build-run.sh "$n" "$o" > $out_file
if [ "$?" -eq 0 ]; then
	DIFF=`diff $out_file ../gui/logic-analyzer/data/test-n$n.log` &&
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

