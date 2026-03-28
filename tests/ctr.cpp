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
    const arr<i32, 0>  a;
    const arr<usz, 10> b = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    LM_CHECK(a.empty());

    for (usz i = 0; i < b.len(); ++i) LM_CHECK(i == b[i]);
    for (const usz e : b) LM_CHECK(e == b[e]);

    LM_TERM();
}
