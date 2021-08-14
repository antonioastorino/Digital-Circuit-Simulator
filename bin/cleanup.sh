#!/bin/bash
set -e
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"

/bin/rm -rf \
	"${BUILD_DIR}" \
	"${MAKE_FILE}" \
	"${LOG_FILE_ERR}" \
	*.list