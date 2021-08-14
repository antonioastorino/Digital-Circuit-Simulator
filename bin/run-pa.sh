#!/bin/zsh
BD="$(pwd)/$(dirname $0)/.."
pushd ${BD}
php -S 127.0.0.1:8081 &
open -a Google\ Chrome.app http://127.0.0.1:8081/gui/performance-analyzer/index.html &
popd