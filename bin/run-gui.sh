#!/bin/bash
base_dir="`pwd`/`dirname $0`/../"
pushd $path
php -S 127.0.0.1:8080 &
open -a Google\ Chrome.app http://127.0.0.1:8080/gui/index.html &
popd