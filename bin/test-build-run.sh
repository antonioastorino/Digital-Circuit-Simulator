#!/bin/zsh
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z $APP_NAME ]; then exit 1; fi

pushd "${BD}"

o="0"
for EXTENSION in ${SRC_EXTENSIONS[@]} ${INC_EXTENSIONS[@]}; do
	for FILE in $(find . -name "*.${EXTENSION}"); do
		clang-format -i $FILE
	done
done

n=""
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

mkdir -p \
	${LOGIC_ANALYZER_DATA_FOLDER} \
	${PERFORMANCE_ANALYZER_DATA_FOLDER}

OUT_FILE="${LOGIC_ANALYZER_DATA_FOLDER}/out-test-n$n.log"

make SHELL=/bin/bash MODE=TEST OPT="$o" 1>/dev/null
if [ "$?" -eq "0" ]; then
	if [ "${n}" = "" ]; then
		build/${APP_NAME}-test-o"$o"
	else
		build/${APP_NAME}-test-o"$o" $n >${OUT_FILE}
	fi
else
	exit $?
fi

if [ $? -eq 0 ]; then
	DIFF=$(diff $OUT_FILE ${EXPECTED_FOLDER}/test-n$n.log)
	echo "Checking..."
	if [ "$DIFF" != "" ]; then
		echo "Error: test $n not passed"
		cat $OUT_FILE
		echo "$DIFF"
	else
		echo "Test $n passed"
	fi
fi
