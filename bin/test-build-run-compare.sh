#!/bin/zsh
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z $APP_NAME ]; then exit 1; fi

pushd "${BD}"

o="0"
if [ "$1" = "" ]; then
	bin/test-build-run.sh "$n"
else 
	n="$1"
fi
[ "$2" != "" ] && o="$2"

mkdir -p ${ARTIFACT_FOLDER}

out_file=${ARTIFACT_FOLDER}/test"-n$n".log

bin/test-build-run.sh "$n" "$o" > $out_file
if [ $? -eq 0 ]; then
	DIFF=`diff $out_file gui/logic-analyzer/data/test-n$n.log`
	echo "Checking..."
	if [ "$DIFF" != "" ]; then
		echo "Error: test $n not passed"
		cat $out_file
		print "$DIFF"
	else
		echo "Test $n passed"
		rm $out_file
	fi
fi

