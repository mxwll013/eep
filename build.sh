#! /usr/bin/env bash

prep() {
    mkdir -p "$(dirname "$1")"
}

compile() {
    local out="build/obj/$1.o"
    prep "$out"

    echo "Compiling $1"

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
    local name="$1"
    local in="build/obj/$name.o"
    local out="build/bin/$name"
    prep "$out"
    shift

    echo "Linking $name"

    mkdir -p "build/bin"
    clang++ -std=c++20 -I include/ -o "$out" "$in" -L build/lib/ "${@/#/-l}"
}

# Build the project

mkdir -p build/obj


srr_sys="src/srr/sys"

lm_exit="src/lm/exit"

ex_hello_world="examples/hello_world"
ex_format="examples/format"

compile "$srr_sys"

compile "$lm_exit"

compile "$ex_hello_world"
compile "$ex_format"

lib "srr" "${srr_sys}.o"
lib "lm" "${lm_exit}.o"

exe "$ex_hello_world" "srr" "lm"
exe "$ex_format" "srr" "lm"
