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

#include <lm/macros.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

i32 main() noexcept {
    str s1{ "Hello, world!" };
    str s2{};

    for (const byte c : s1) s2.push(c);

    LM_CHECK(s1.prefix("Hello"));
    LM_CHECK(s1.suffix("world!"));

    LM_CHECK(s2.prefix("Hello"));
    LM_CHECK(s2.suffix("world!"));

    LM_DBG("[s1] len = {}", s1.len());
    LM_DBG("[s1] cap = {}", s1.cap());

    LM_DBG("[s2] len = {}", s2.len());
    LM_DBG("[s2] cap = {}", s2.cap());

    LM_DBG("[s1] '{}'", s1);
    LM_DBG("[s2] '{}'", s2);

    LM_TERM();
}
