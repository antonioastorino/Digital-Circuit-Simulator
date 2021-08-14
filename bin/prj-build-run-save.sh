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

filename="gui/logic-analyzer/data/prj-n$n.log"

bin/prj-build-run.sh "$n" "$o" | tee $filename
if ! [ -s $filename ]; then
	rm $filename
fi