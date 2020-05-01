#!/bin/bash
base_dir="`pwd`/`dirname $0`/../"
pushd $path
php -S 127.0.0.1:8081 &
open -a Google\ Chrome.app http://127.0.0.1:8081/gui/performance-analyzer/index.html &
popd