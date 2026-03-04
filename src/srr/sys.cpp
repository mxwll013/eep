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

#include "srr/sys.hpp"

#include "srr/err.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

#include <unistd.h>

inline namespace srr {
namespace sys {

void exit(exitc c) noexcept { ::_exit(static_cast<int>(c)); }

err  write(sink s, strv v) noexcept {
    const isize w = ::write(static_cast<int>(s), v.data(), v.len());

    if (w < 0) return errc::SYS_WRITE_FAIL;

    return {};
}

} // namespace sys
} // namespace srr
