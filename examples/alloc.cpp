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
#include <srr/mem.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

i32 main() noexcept {
    const usz  n = 13;

    const strb buf{ mem::alloc<char>(n), n };

    const usz  m = buf.copy("Hello, world!");

    LM_CHECK(n == m);

    LM_LOG("{}", buf);

    mem::dealloc(buf.data(), n);

    LM_TERM();
}
