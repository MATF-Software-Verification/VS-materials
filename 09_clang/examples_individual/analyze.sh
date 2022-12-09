#!/bin/bash

if [ $# -lt 1 ]; then
    echo "usage: source_file checker[,checker,...] [extra analyzer args]"
    exit 1
fi

function show_source ()
{
    if command -v bat ; then
        bat $@
    else
        cat -ns $@
    fi
}

SOURCE=$1
shift 1
EXTRA_ARGS=$@

set -xe;
show_source $SOURCE

rm -rf tmp
scan-build \
    -enable-checker $@ \
    -o tmp \
    -v \
    clang $SOURCE

scan-view tmp/*
