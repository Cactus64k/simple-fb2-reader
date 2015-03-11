#!/bin/bash
export INCLUDE=`pkg-config --cflags-only-I gtk+-3.0`
export CFG_COUNT=1
cppcheck -j8 -q --inconclusive --library=gtk --enable=all --std=c99 --report-progress --max-configs=$CFG_COUNT $INCLUDE ./src/
echo '\nDone\n'
read
