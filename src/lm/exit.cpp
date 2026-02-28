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

#include "lm/exit.hpp"

#include "lm/log.hpp"

#include <srr/err.hpp>
#include <srr/str.hpp>
#include <srr/sys.hpp>

namespace lm {

void exit(err e) noexcept {
    if (e) log(fmt(e));
    sys::exit(e.cast());
}

void exit(errc c) noexcept {
    if (c != errc::OK) log(fmt(c));
    sys::exit(cast(c));
}

void exit(exitc c) noexcept {
    if (c != exitc::OK) log(fmt(c));
    sys::exit(c);
}

void assert(bool c) noexcept {
    if (c) exit(Exitc::ASSERT);
}

void assert(bool c, strv msg) noexcept {
    if (c) {
        log(msg);
        exit(Exitc::ASSERT);
    }
}

} // namespace lm
