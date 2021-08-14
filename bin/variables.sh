#!/bin/bash
APP_NAME="dcs"
COMMON_HEADER="include/DCSCommon.hpp"
CPPFLAGS="-Wall -Wextra -g -std=c++1z"
MAINFLAGS="-Wall -Wextra -g -std=c++1z"
GLOBAL_COMPILER="clang"
LIB="-lc++"
BUILD_DIR="build"
MAKE_FILE="Makefile"
MAIN="main"
MAIN_TEST="main-test"
SRC_EXTENSIONS=("cpp")
INC_EXTENSIONS=("hpp")

HEADER_PATHS="include"
SRC_PATHS="src"

ARTIFACT_FOLDER="test/artifacts"

LOG_FILE_ERR="test/test-err.log"
