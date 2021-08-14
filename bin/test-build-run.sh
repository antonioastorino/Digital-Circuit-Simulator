#!/bin/zsh
set -e
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z $APP_NAME ]; then exit 1; fi

pushd "${BD}"

for EXTENSION in ${SRC_EXTENSIONS[@]} ${INC_EXTENSIONS[@]}; do
    for FILE in $(find . -name "*.${EXTENSION}"); do
        clang-format -i $FILE
    done
done

n=""
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

make SHELL=/bin/bash MODE=TEST OPT="$o" 1>/dev/null
if [ "$?" -eq "0" ]; then
	[ "$n" != "" ] && build/${APP_NAME}-test-o"$o" "$n" || build/${APP_NAME}-test-o"$o"
fi