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

#include "srr/ctr.hpp"

#include <lm/macros.hpp>
#include <srr/types.hpp>

#include <cassert>

i32 main() noexcept {
    const arr<i32, 0>  a;
    const arr<i32, 10> b = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (usize i = 0; i < b.len(); ++i) LM_ASSERT(i == b[i]);
    for (i32 e : b) LM_ASSERT(e == b[e]);

    LM_EXIT();
}
