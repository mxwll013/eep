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
#include <srr/opt.hpp>
#include <srr/types.hpp>

namespace {

res<i32> func(i32 v) noexcept {
    if (v > 0) return v * 2;

    return err{ "Value must be positive" };
}

void check(const res<i32> &r) noexcept {
    if (r.ok())
        LM_INFO("{}", r.unwrap());
    else
        LM_ERR("{}", r.err());
}

} // namespace

i32 main() noexcept {
    const res<i32> r1 = func(120);
    const res<i32> r2 = func(-10);

    check(r1);
    check(r2);

    LM_EXIT();
}
