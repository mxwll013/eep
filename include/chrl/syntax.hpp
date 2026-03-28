/*
 * ------------------------------------------------------------------------------
 * Echo Engine Project - MIT License
 *
 * Part of the Echo Engine Project,
 * A simple and fast game engine built in C++20.
 *
 * https://echoengine.org
 *
 * Copyright (c) 2026 EEP contributors
 * ------------------------------------------------------------------------------
 */

#ifndef CHRL_SYNTAX_HPP_
#define CHRL_SYNTAX_HPP_

#include <srr/ctr.hpp>
#include <srr/err.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

namespace chrl {

struct Flag;
struct Parg;
struct Cmd;
class Ctx;

template<usz N> using FlagArr = arr<cref<Flag>, N>;
template<usz N> using PargArr = arr<cref<Parg>, N>;
template<usz N> using CmdArr  = arr<cref<Cmd>, N>;

using FlagSpan                = span<const cref<Flag>>;
using PargSpan                = span<const cref<Parg>>;
using CmdSpan                 = span<const cref<Cmd>>;

using FlagId                  = u8;
using Hook                    = err (*)(const Ctx &);

struct Flag {
    strv   name;
    strv   desc;
    FlagId id   = 0;
    char   shrt = 0;
};

struct Parg {
    strv name;
    strv desc;
};

struct Cmd {
    strv     name;
    strv     desc;

    CmdSpan  subs;
    PargSpan pargs;

    Hook     hook = nullptr;
};

struct Cli {
    FlagSpan  flags;
    cref<Cmd> root;
    usz       ver_maj = 0;
    usz       ver_min = 0;
    bool      dbg     = true;
};

} // namespace chrl

#endif // CHRL_SYNTAX_HPP_
