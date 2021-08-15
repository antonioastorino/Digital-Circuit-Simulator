#!/bin/bash
set -e
BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"

/bin/rm -rf \
	"${BUILD_DIR}" \
	"${MAKE_FILE}" \
	"${LOGIC_ANALYZER_DATA_FOLDER}"/* \
	"${PERFORMANCE_ANALYZER_DATA_FOLDER}"/* \
	*.list