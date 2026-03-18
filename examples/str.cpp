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
    const str s{ "Hello, world!" };

    LM_ASSERT(s.prefix("Hello"));
    LM_ASSERT(s.suffix("world!"));

    LM_DBG("[s] len = {}", s.len());
    LM_DBG("[s] cap = {}", s.cap());
    LM_DBG("[s] empty = {}", s.empty());

    LM_DBG("[s] '{}'", s);

    LM_EXIT();
}
