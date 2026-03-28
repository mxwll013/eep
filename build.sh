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


srr_impl_alloc="src/srr/impl/Alloc"
srr_sys="src/srr/sys"
srr_mem="src/srr/mem"

lm_panic="src/lm/panic"

chrl_cli="src/chrl/cli"

ts_ctr="tests/ctr"
ts_mem="tests/mem"

ex_alloc="examples/alloc"
ex_check="examples/check"
ex_cli="examples/cli"
ex_format="examples/format"
ex_hello_world="examples/hello_world"
ex_list="examples/list"
ex_logging="examples/logging"
ex_result="examples/result"
ex_str="examples/str"

compile "$srr_impl_alloc"
compile "$srr_sys"
compile "$srr_mem"

compile "$lm_panic"

compile "$chrl_cli"

compile "$ts_ctr"
compile "$ts_mem"

compile "$ex_alloc"
compile "$ex_check"
compile "$ex_cli"
compile "$ex_format"
compile "$ex_hello_world"
compile "$ex_list"
compile "$ex_logging"
compile "$ex_result"
compile "$ex_str"

lib "srr" "${srr_sys}.o" "${srr_mem}.o" "${srr_impl_alloc}.o"
lib "lm" "${lm_panic}.o"
lib "chrl" "${chrl_cli}.o"

exe "$ts_ctr" "srr" "lm"
exe "$ts_mem" "srr" "lm"

exe "$ex_alloc" "srr" "lm"
exe "$ex_check" "srr" "lm"
exe "$ex_cli" "srr" "lm" "chrl"
exe "$ex_format" "srr" "lm"
exe "$ex_hello_world" "srr" "lm"
exe "$ex_list" "srr" "lm"
exe "$ex_logging" "srr" "lm"
exe "$ex_result" "srr" "lm"
exe "$ex_str" "srr" "lm"
