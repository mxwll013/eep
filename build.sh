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

lm_panic="src/lm/panic"

ex_hello_world="examples/hello_world"
ex_format="examples/format"
ex_assert="examples/assert"
ex_logging="examples/logging"

compile "$srr_sys"

compile "$lm_panic"

compile "$ex_hello_world"
compile "$ex_format"
compile "$ex_assert"
compile "$ex_logging"

lib "srr" "${srr_sys}.o"
lib "lm" "${lm_panic}.o"

exe "$ex_hello_world" "srr" "lm"
exe "$ex_format" "srr" "lm"
exe "$ex_assert" "srr" "lm"
exe "$ex_logging" "srr" "lm"
