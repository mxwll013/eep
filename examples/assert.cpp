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
#include <srr/types.hpp>

i32 main() {
    LM_ASSERT(1 == 1, "This will pass");
    LM_ASSERT(1 != 1, "This will not pass");

    LM_UNREACH();
}
