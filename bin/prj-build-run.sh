#!/bin/zsh
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z $APP_NAME ]; then exit 1; fi

pushd "${BD}"

for EXTENSION in ${SRC_EXTENSIONS[@]} ${INC_EXTENSIONS[@]}; do
	for FILE in $(find . -name "*.${EXTENSION}"); do
		clang-format -i ${FILE}
	done
done

PRJ_NUMBER=
OPT_LEVEL=0
while getopts o:n: flag
do
    case "${flag}" in
        o) OPT_LEVEL=${OPTARG};;
        n) PRJ_NUMBER=${OPTARG};;
    esac
done

mkdir -p \
	${LOGIC_ANALYZER_DATA_FOLDER} \
	${PERFORMANCE_ANALYZER_DATA_FOLDER}

OUT_FILE="${LOGIC_ANALYZER_DATA_FOLDER}/out-prj-n${PRJ_NUMBER}.log"

make SHELL=/bin/bash OPT="${OPT_LEVEL}" 1>/dev/null
if [ "$?" -eq "0" ]; then
	if [ "${PRJ_NUMBER}" = "" ]; then
		build/${APP_NAME}-o"${OPT_LEVEL}" 
	else
		build/${APP_NAME}-o"${OPT_LEVEL}" ${PRJ_NUMBER} | tee ${OUT_FILE}
	fi
else
	exit $?
fi
