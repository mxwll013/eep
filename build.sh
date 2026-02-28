#! /usr/bin/env bash

prep() {
    mkdir -p "$(dirname "$1")"
}

dirty() {
    if [[ ! -f "$2" ]]; then
        return 0
    fi

    if [[ "$1" -nt "$2" ]]; then
        return 0
    fi

    return 1
}

compile() {
    local out="build/obj/$1.o"
    prep "$out"

    if dirty "$1.cpp" "$out"; then
        echo "Compiling $1"
    else
        echo "Skipping $1, up to date."
        return
    fi

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
lm_log="src/lm/log"

ex_hello_world="examples/hello_world"

compile "$srr_sys"

compile "$lm_exit"
compile "$lm_log"

compile "$ex_hello_world"

lib "srr" "${srr_sys}.o"
lib "lm" "${lm_exit}.o" "${lm_log}.o"

exe "$ex_hello_world" "srr" "lm"
