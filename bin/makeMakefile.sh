BD="$(pwd)/$(dirname $0)/.."
source "${BD}/bin/variables.sh"
if [ -z ${APP_NAME} ]; then exit 1; fi

set -e

pushd "$BD"
bin/cleanup.sh

function pf() { printf "$1" >>"$MAKE_FILE"; }

pf "# Makefile auto generated using custom generator"
# Find all the directories containing header files

cat /dev/null >header-dir.list # dir only
cat /dev/null >src-full.list   # full path
cat /dev/null >src-name.list   # filename no extension

for EXTENSION in ${SRC_EXTENSIONS[@]}; do
	for f in $(find $SRC_PATHS -name "*.${EXTENSION}"); do
		FILE_NAME=$(basename $f)
		echo "$f" >>src-full.list
		FILE_NO_EXT=${FILE_NAME%.*}
		echo "${FILE_NO_EXT}" >>src-name.list
	done
done

for EXTENSION in ${INC_EXTENSIONS[@]}; do
	for f in $(find $HEADER_PATHS -name "*.${EXTENSION}"); do
		echo $(dirname $f) >>header-dir.list
	done
done

# Remove duplicates from directory list
sort header-dir.list | uniq >header-sorted-dir.list

# find system libs which may need to be linked
ALL_LIBS=$(egrep -rh "^#include|^#import" $(echo "$SRC_PATHS" "$HEADER_PATHS") 2>/dev/null | grep -o "<.*>" | sed 's/<//' | sed 's/>//' | sort | uniq)

# select those who actually need to be linked and create LIB list
for LIB_FOUND in ${ALL_LIBS[@]}; do
	case $LIB_FOUND in
	thread)
		LIB="$LIB -pthread"
		;;
	curl/curl.h)
		LIB="$LIB -lcurl"
		;;
	zlib.h)
		LIB="$LIB -lz"
		;;
	Cocoa/Cocoa.h)
		FRAMEWORKS="Cocoa ${FRAMEWORKS}"
		;;
	esac
done

pf "\nOBJCFLAGS=${OBJCFLAGS}"
pf "\nCPPFLAGS=${CPPFLAGS}"
pf "\nCFLAGS=${CFLAGS}"
pf "\nMAINFLAGS=${MAINFLAGS}"
pf "\nBD=${BD}"
pf "\nOPT ?= 0"

[ "$LIB" != "" ] && pf "\nLIB=$LIB"                                 # LIB added if not empty
[ "$FRAMEWORKS" != "" ] && pf "\nFRAMEWORKS=-framework $FRAMEWORKS" # LIB added if not empty
pf "\nINC="
while read -r folder; do # created -I list
	pf " -I$folder \\"
	pf "\n"
done <header-sorted-dir.list

# Phony recipies
pf "\n.PHONY: all setup"
pf "\n"

# All
pf "\nall: setup"
pf "\n"

pf "\nsetup:"
pf "\n\t@/bin/rm -rf ${APP_NAME}.app"
pf "\n\t@mkdir -p \\"
pf "\n\t${BUILD_DIR}"

# Set TEST to 1 in case MODE==TEST and run unit tests
pf "\n\t@if [ \"\$(MODE)\" = \"TEST\" ]; then \\"
pf "\n\t[ \`grep -c '^#define TEST 0' \"\$(BD)\"/${COMMON_HEADER}\` -eq 1 ] && \\"
pf "\n\tsed -i.bak 's/^#define TEST 0/#define TEST 1/g' \"\$(BD)\"/${COMMON_HEADER}; \\"
pf "\n\tmake -C \"\$(BD)\" OPT=\$(OPT) ${BUILD_DIR}/${APP_NAME}-test-o\$(OPT); \\"
pf "\n\telse \\"

# Reset TEST in case as default behavior.
pf "\n\t[ \`grep -c '^#define TEST 1' \"\$(BD)\"/${COMMON_HEADER}\` -eq 1 ] && \\"
pf "\n\tsed -i.bak 's/^#define TEST 1/#define TEST 0/g' \"\$(BD)\"/${COMMON_HEADER}; \\"
pf "\n\tmake -C \"\$(BD)\" OPT=\$(OPT) ${BUILD_DIR}/${APP_NAME}-o\$(OPT); \\"
pf "\n\tfi"
pf "\n"

pf "\n${BUILD_DIR}/${APP_NAME}-o\$(OPT):"
while read -r FILE_NAME; do
	if [ "${FILE_NAME}" == "${MAIN_TEST}" ]; then continue; fi
	pf "\\"
	pf "\n\t${BUILD_DIR}/${FILE_NAME}-o\$(OPT).o "
done <src-name.list
pf "\n\t${GLOBAL_COMPILER} \$(LIB) \$(MAINFLAGS) -O\$(OPT) \$(INC) \$(FRAMEWORKS) \$^ -o \$@"
pf "\n"

# Test
pf "\n${BUILD_DIR}/${APP_NAME}-test-o\$(OPT):"
while read -r FILE_NAME; do
	if [ "${FILE_NAME}" == "${MAIN}" ]; then continue; fi
	pf "\\"
	pf "\n\t${BUILD_DIR}/${FILE_NAME}-o\$(OPT).o "
done <src-name.list
pf "\n\t${GLOBAL_COMPILER} \$(LIB) \$(MAINFLAGS) -O\$(OPT) \$(INC) \$(FRAMEWORKS) \$^ -o \$@"
pf "\n"

echo "Adding dependency list"
while read -r FILE_FULL_PATH; do
	FILE_NAME=$(basename "${FILE_FULL_PATH}")
	DIR_NAME=$(dirname "${FILE_FULL_PATH}")
	FILE_NO_EXT=${FILE_NAME%.*}
	FILE_EXT=${FILE_NAME##*.}

	pf "\n${BUILD_DIR}/${FILE_NO_EXT}-o\$(OPT).o: ${FILE_FULL_PATH} "

	HEADER_FILES=$(egrep "^#include|^#import" "${FILE_FULL_PATH}" | grep -v "<" | awk -F '"' '{print $2}')

	for HEADER_FILE in ${HEADER_FILES[@]}; do
		# Some headers are imported with the path
		HEADER_NAME=$(basename "${HEADER_FILE}")
		HEADER_PATH=$(find "${BD}" -name "${HEADER_NAME}")
		HEADER_PATH_FROM_BD=${HEADER_PATH#"${BD}/"}
		pf "\\"
		pf "\n\t${HEADER_PATH_FROM_BD} "
	done

	case $FILE_EXT in
	c)
		pf "\n\tgcc \$(INC) \$(CFLAGS) -O\$(OPT) -c \$< -o \$@\n"
		;;
	cpp)
		pf "\n\tg++ \$(INC) \$(CPPFLAGS) -O\$(OPT) -c \$< -o \$@\n"
		;;
	mm)
		pf "\n\tclang \$(INC) \$(OBJCFLAGS) -O\$(OPT) -c \$< -o \$@\n"
		;;
	esac
	pf "\n"
done <src-full.list

rm *.list

popd
