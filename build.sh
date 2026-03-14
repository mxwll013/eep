#! /usr/bin/env bash

prep() {
    mkdir -p "$(dirname "$1")"
}

compile() {
    echo "Compiling $1"

    local out="build/obj/$1.o"
    prep "$out"

    clang++ -std=c++20 -I include/ -c "$1.cpp" -o "$out"
}

lib() {

    echo "Linking lib$1"

    local out="build/lib/lib$1.a"
    prep "$out"
    shift

    ar rcs "$out" "${@/#/build/obj/}"
}

exe() {
    echo "Linking $1"

    local name="$1"
    local in="build/obj/$name.o"
    local out="build/bin/$name"
    prep "$out"
    shift


    mkdir -p "build/bin"
    clang++ -std=c++20 -I include/ -o "$out" "$in" -L build/lib/ "${@/#/-l}"
}

# Build the project

mkdir -p build/obj


srr_sys="src/srr/sys"
srr_mem="src/srr/mem"

lm_panic="src/lm/panic"

ts_ctr="tests/ctr"
ts_mem="tests/mem"

ex_assert="examples/assert"
ex_format="examples/format"
ex_hello_world="examples/hello_world"
ex_logging="examples/logging"
ex_result="examples/result"

compile "$srr_sys"
compile "$srr_mem"

compile "$lm_panic"

compile "$ts_ctr"
compile "$ts_mem"

compile "$ex_hello_world"
compile "$ex_format"
compile "$ex_assert"
compile "$ex_logging"
compile "$ex_result"

lib "srr" "${srr_sys}.o" "${srr_mem}.o"
lib "lm" "${lm_panic}.o"

exe "$ts_ctr" "srr" "lm"
exe "$ts_mem" "srr" "lm"

exe "$ex_hello_world" "srr" "lm"
exe "$ex_format" "srr" "lm"
exe "$ex_assert" "srr" "lm"
exe "$ex_logging" "srr" "lm"
exe "$ex_result" "srr" "lm"
