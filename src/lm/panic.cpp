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
    LM_TRC("{} : {}", t.file, t.line);
    LM_ERR("{}", msg);
    LM_TERM(ter::PANIC);
}

void panic(Trace &&t, err e) noexcept {
    LM_TRC("{} : {}", t.file, t.line);
    LM_ERR("{}", e);
    LM_TERM(ter::PANIC);
}

void panic(Trace &&t) noexcept {
    LM_TRC("{} : {}", t.file, t.line);
    LM_TERM(ter::PANIC);
}

void panic(strv msg) noexcept {
    LM_ERR("{}", msg);
    LM_TERM(ter::PANIC);
}

void panic(err e) noexcept {
    LM_ERR("{}", e);
    LM_TERM(ter::PANIC);
}

void panic() noexcept {
    // ...
    LM_TERM(ter::PANIC);
}

void term(ter e) noexcept {
    const terc c = e.code();

    switch (c) {
    case ter::OK     : break;
    case ter::PANIC  : [[fallthrough]];
    case ter::UNREACH: [[fallthrough]];
    case ter::CHECK  : LM_PAN("{}", e); break;
    default          : LM_ERR("{}", e); break;
    }

    sys::exit(c);
}

void term(err e) noexcept {
    if (!e) sys::exit({});

    LM_ERR("{}", e);
    LM_TERM(e.ter());
}

void term() noexcept {
    // ...
    sys::exit({});
}

void unreach(Trace &&t, strv msg) noexcept {
    LM_TRC("{} : {}", t.file, t.line);
    LM_ERR("{}", msg);
    LM_TERM(ter::UNREACH);
}

void unreach(Trace &&t) noexcept {
    LM_TRC("{} : {}", t.file, t.line);
    LM_TERM(ter::UNREACH);
}

void unreach(strv msg) noexcept {
    LM_ERR("{}", msg);
    LM_TERM(ter::UNREACH);
}

void unreach() noexcept {
    // ...
    LM_TERM(ter::UNREACH);
}

void check(Trace &&t, bool c, strv s, strv msg) noexcept {
    if (c) return;

    LM_TRC("{} : {}", t.file, t.line);
    LM_TRC("'{}'", s);
    LM_ERR("{}", msg);
    LM_TERM(ter::CHECK);
}

void check(Trace &&t, bool c, strv s) noexcept {
    if (c) return;

    LM_TRC("{} : {}", t.file, t.line);
    LM_TRC("'{}'", s);
    LM_TERM(ter::CHECK);
}

void check(bool c, strv s, strv msg) noexcept {
    if (c) return;

    LM_TRC("'{}'", s);
    LM_ERR("{}", msg);
    LM_TERM(ter::CHECK);
}

void check(bool c, strv s) noexcept {
    if (c) return;

    LM_TRC("'{}'", s);
    LM_TERM(ter::CHECK);
}

} // namespace lm
