#!/bin/zsh
set -e
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z $APP_NAME ]; then exit 1; fi

pushd "${BD}"
n=""
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

for EXTENSION in ${SRC_EXTENSIONS[@]} ${INC_EXTENSIONS[@]}; do
    for FILE in $(find . -name "*.${EXTENSION}"); do
        clang-format -i $FILE
    done
done

make SHELL=/bin/bash OPT="$o" 1>/dev/null
if [ "$?" -eq "0" ]; then
	build/${APP_NAME}-o"$o" "$n"
fi