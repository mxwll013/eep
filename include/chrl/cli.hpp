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

#ifndef CHRL_CLI_HPP_
#define CHRL_CLI_HPP_

#include "chrl/syntax.hpp"

#include <srr/ctr.hpp>
#include <srr/err.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

#define CHRL_ENTRY(...)                                                        \
    i32 main(i32 argc, char **argv) noexcept {                                 \
        chrl::entry((__VA_ARGS__), argc, argv);                                \
    }

namespace chrl {

struct Parsed {
    list<strv>      args;
    list<cref<Cmd>> path;
    list<strv>      pargs;
    err             err;

    u64             flags;
    bool            builtin;
};

class Ctx {
public:
    Ctx(const Cli &cli, const list<strv> &args) noexcept;

    [[nodiscard]] bool       flag(FlagId id) const noexcept;
    [[nodiscard]] bool       ok() const noexcept;
    [[nodiscard]] const err &err() const noexcept;
    [[nodiscard]] const Cli &cli() const noexcept;
    [[nodiscard]] Hook       hook() const noexcept;

private:
    cref<Cli> cli_;
    Parsed    parsed_;
};

[[noreturn]] void entry(const Cli &cli, i32 argc, char **argv) noexcept;

} // namespace chrl

#endif // CHRL_CLI_HPP_
