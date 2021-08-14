#!/bin/zsh
set -e
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z $APP_NAME ]; then exit 1; fi

# Accept case-insensitive "test" by converting to uppercase
MODE="$1"
MODE=${MODE:u}

function analyze_logs() {
    echo " Log analysis started."
    RET_VAL=$1
    if [ ${RET_VAL} -ne 0 ]; then
        echo -e "\n\n\e[31mFAIL\e[0m - Execution interrupted with error code ${RET_VAL}.\n\n"
        exit ${RET_VAL}
    fi
    if [ -f "${LOG_FILE_ERR}" ]; then
        if [ "$(cat ${LOG_FILE_ERR})" = "" ]; then
            echo -e "\n\e[32mSUCCESS\e[0m - All tests passed.\n\n"
        else
            echo -e "\n\e[31mFAIL\e[0m - The content of ${LOG_FILE_ERR} follows.\n\n"
            cat "${LOG_FILE_ERR}"
        fi
    else
        echo -e "\n\n\e[31mApplication not run.\e[0m\n\n"
    fi
    echo " Log analysis completed."
}

function analyze_mem() {
    echo " Memory report analysis started."
    echo
    if [ $(ls /tmp/pointers | wc -l) -ne 0 ]; then
        echo "\e[33mFAIL:\e[0m Memory leak detected."
        for f in $(ls /tmp/pointers); do
            echo "$f - $(cat /tmp/pointers/$f)"
        done
    else
        echo "\e[32mSUCCESS\e[0m - No memory leak detected."
    fi
    set -e
    echo
    echo " Memory report analysis completed."
}

pushd "${BD}"
set +e
/bin/rm -rf /tmp/pointers
set -e

if ! [ -f "${MAKE_FILE}" ]; then
    echo "No makefile found."
    echo "Calling bin/makeMakefile.sh"
    ./bin/makeMakefile.sh
fi

for EXTENSION in ${SRC_EXTENSIONS[@]} ${INC_EXTENSIONS[@]}; do
    for FILE in $(find . -name "*.${EXTENSION}"); do
        clang-format -i $FILE
    done
done

mkdir -p /tmp/pointers

echo "Running"
if [ "${MODE}" = "TEST" ] || [ "${MODE}" = "DEBUG" ]; then
    /bin/rm -rf ${ARTIFACT_FOLDER}/*
    # Set up dir entries for testing.
    mkdir -p "${ARTIFACT_FOLDER}/empty/" \
        "${ARTIFACT_FOLDER}/non-empty/inner/inner_l2" \
        "${ARTIFACT_FOLDER}/non-empty-0/inner/inner_l2" \
        "${ARTIFACT_FOLDER}/empty-0"

    touch "${ARTIFACT_FOLDER}/non-empty/inner/file.txt"
    touch "${ARTIFACT_FOLDER}/non-empty/inner/inner_l2/file.txt"
    touch "${ARTIFACT_FOLDER}/delete_me.txt"
    make MODE=TEST
    if [ "${MODE}" = "TEST" ]; then
        # Remove previous logs.
        ./build/"${APP_NAME}-test" 2>"${LOG_FILE_ERR}"
        RET_VAL=$?
        echo ""
        echo "================================================================================"
        analyze_logs ${RET_VAL}
        echo "================================================================================"
        analyze_mem
    else
        lldb ./build/"${APP_NAME}-test"
    fi
else
    make
    ./build/"${APP_NAME}"
fi
popd
