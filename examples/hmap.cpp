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
#include <srr/err.hpp>
#include <srr/hash.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

i32 main() noexcept {
    hmap<strv, u32> m;

    LM_DBG("cap = {}", m.cap());

    const err e1 = m.empl("a", 2_u32);
    const err e2 = m.empl("b", 3_u32);

    LM_CHECK(e1.ok());
    LM_CHECK(e2.ok());
    LM_CHECK(m.len() == 2);

    LM_DBG("cap = {}", m.cap());
    LM_DBG("m[a] : {}", *m["a"]);
    LM_DBG("m[b] : {}", *m["b"]);

    // res<cref<u64>> r = m.at(1);

    // LM_CHECK(r.unwrap() == 2);

    LM_TERM();
}
