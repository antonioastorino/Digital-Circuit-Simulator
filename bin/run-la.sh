#!/bin/zsh
BD="$(pwd)/$(dirname $0)/.."
pushd ${BD}
php -S 127.0.0.1:8080 &
open -a Google\ Chrome.app http://127.0.0.1:8080/gui/logic-analyzer/index.html &
popd