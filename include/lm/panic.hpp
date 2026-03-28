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

#ifndef LM_PANIC_HPP_
#define LM_PANIC_HPP_

#include <srr/err.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

namespace lm {

struct Trace {
    strv file;
    u32  line = 0;
};

[[noreturn]] void panic(Trace &&t, strv msg) noexcept;
[[noreturn]] void panic(Trace &&t, err e) noexcept;
[[noreturn]] void panic(Trace &&t) noexcept;
[[noreturn]] void panic(strv msg) noexcept;
[[noreturn]] void panic(err e) noexcept;
[[noreturn]] void panic() noexcept;

[[noreturn]] void term(ter e) noexcept;
[[noreturn]] void term(err e) noexcept;
[[noreturn]] void term() noexcept;

[[noreturn]] void unreach(Trace &&t, strv msg) noexcept;
[[noreturn]] void unreach(Trace &&t) noexcept;
[[noreturn]] void unreach(strv msg) noexcept;
[[noreturn]] void unreach() noexcept;

void              check(Trace &&t, bool c, strv s, strv msg) noexcept;
void              check(Trace &&t, bool c, strv s) noexcept;
void              check(bool c, strv s, strv msg) noexcept;
void              check(bool c, strv s) noexcept;

} // namespace lm

#endif // LM_PANIC_HPP_
