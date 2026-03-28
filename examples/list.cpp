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
#include <srr/ctr.hpp>
#include <srr/types.hpp>

i32 main() noexcept {
    list<i32> li;

    LM_CHECK(li.cap() == 0);
    LM_CHECK(li.len() == 0);
    LM_CHECK(li.empty());

    for (i32 i = 0; i < 10; ++i) li.push(i * i);

    LM_CHECK(li.cap() >= 10);
    LM_CHECK(li.len() == 10);
    LM_CHECK(!li.empty());

    for (usz i = 0; i < li.len(); ++i) LM_DBG("[{}] = {}", i, li[i]);

    LM_TERM();
}
