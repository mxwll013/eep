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

#include "lm/panic.hpp"

#include "lm/macros.hpp"

#include <srr/err.hpp>
#include <srr/str.hpp>
#include <srr/sys.hpp>

namespace lm {

void panic(Trace &&t, strv msg) noexcept {
    LM_INFO("{} : {}", t.file, t.line);
    LM_ERR("{}", msg);
    LM_EXIT(exitc::PANIC);
}

void panic(Trace &&t, err e) noexcept {
    LM_INFO("{} : {}", t.file, t.line);
    LM_ERR("{}", e);
    LM_EXIT(exitc::PANIC);
}

void panic(Trace &&t) noexcept {
    LM_INFO("{} : {}", t.file, t.line);
    LM_EXIT(exitc::PANIC);
}

void panic(strv msg) noexcept {
    LM_ERR("{}", msg);
    LM_EXIT(exitc::PANIC);
}

void panic(err e) noexcept {
    LM_ERR("{}", e);
    LM_EXIT(exitc::PANIC);
}

void panic() noexcept {
    // ...
    LM_EXIT(exitc::PANIC);
}

void exit(exitc c) noexcept {
    switch (c) {
    case exitc::OK         : break;
    case exitc::PANIC      : [[fallthrough]];
    case exitc::UNREACHABLE: [[fallthrough]];
    case exitc::ASSERT     : LM_PAN("{}", c); break;
    default                : LM_ERR("{}", c); break;
    }

    sys::exit(c);
}

void exit() noexcept {
    // ...
    sys::exit({});
}

void unreach(Trace &&t, strv msg) noexcept {
    LM_INFO("{} : {}", t.file, t.line);
    LM_ERR("{}", msg);
    LM_EXIT(exitc::UNREACHABLE);
}

void unreach(Trace &&t) noexcept {
    LM_INFO("{} : {}", t.file, t.line);
    LM_EXIT(exitc::UNREACHABLE);
}

void unreach(strv msg) noexcept {
    LM_ERR("{}", msg);
    LM_EXIT(exitc::UNREACHABLE);
}

void unreach() noexcept {
    // ...
    LM_EXIT(exitc::UNREACHABLE);
}

void assert(Trace &&t, bool c, strv s, strv msg) noexcept {
    if (c) return;

    LM_INFO("{} : {}", t.file, t.line);
    LM_INFO("{}", s);
    LM_ERR("{}", msg);
    LM_EXIT(exitc::ASSERT);
}

void assert(Trace &&t, bool c, strv s) noexcept {
    if (c) return;

    LM_INFO("{} : {}", t.file, t.line);
    LM_INFO("{}", s);
    LM_EXIT(exitc::ASSERT);
}

void assert(bool c, strv s, strv msg) noexcept {
    if (c) return;

    LM_INFO("{}", s);
    LM_ERR("{}", msg);
    LM_EXIT(exitc::ASSERT);
}

void assert(bool c, strv s) noexcept {
    if (c) return;

    LM_INFO("{}", s);
    LM_EXIT(exitc::ASSERT);
}

} // namespace lm
