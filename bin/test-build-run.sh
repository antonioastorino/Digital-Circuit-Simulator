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

TEST_NUMBER=
OPT_LEVEL=0
while getopts o:n: flag
do
    case "${flag}" in
        o) OPT_LEVEL=${OPTARG};;
        n) TEST_NUMBER=${OPTARG};;
    esac
done

mkdir -p \
	${LOGIC_ANALYZER_DATA_FOLDER} \
	${PERFORMANCE_ANALYZER_DATA_FOLDER}

OUT_FILE="${LOGIC_ANALYZER_DATA_FOLDER}/out-test-n${TEST_NUMBER}.log"

make SHELL=/bin/bash MODE=TEST OPT="${OPT_LEVEL}" 1>/dev/null
if [ "$?" -eq "0" ]; then
	if [ "${TEST_NUMBER}" = "" ]; then
		build/${APP_NAME}-test-o"${OPT_LEVEL}"
	else
		build/${APP_NAME}-test-o"${OPT_LEVEL}" ${TEST_NUMBER} >${OUT_FILE}
	fi
else
	exit $?
fi

if [ $? -eq 0 ]; then
	DIFF=$(diff $OUT_FILE ${EXPECTED_FOLDER}/test-n${TEST_NUMBER}.log)
	echo "Checking..."
	if [ "$DIFF" != "" ]; then
		echo "Error: test ${TEST_NUMBER} not passed"
		cat $OUT_FILE
		echo "$DIFF"
	else
		echo "Test ${TEST_NUMBER} passed"
	fi
fi
