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
#include <srr/opt.hpp>
#include <srr/types.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
struct Test {
    static usize alloc_count;
    static usize dealloc_count;

    // NOLINTNEXTLINE(readability-named-parameter, hicpp-named-parameter)
    Test(const Test &) noexcept { ++alloc_count; }

    Test() noexcept { ++alloc_count; }

    ~Test() noexcept { ++dealloc_count; }
};

usize Test::alloc_count   = 0;
usize Test::dealloc_count = 0;

i32   main() noexcept {
    {
        const Test         t;
        const arr<Test, 3> a = { t, t, t };

        const res<Test>    r = { t };

        LM_ASSERT(Test::alloc_count == 5);
        LM_ASSERT(Test::dealloc_count == 0);
    }

    LM_ASSERT(Test::dealloc_count == 5);
    LM_EXIT();
}
