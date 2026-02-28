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

#ifndef SRR_SYS_HPP_
#define SRR_SYS_HPP_

#include "srr/err.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace sys {

// NOLINTBEGIN(readability-identifier-naming)

using sink             = u8;

// NOLINTEND(readability-identifier-naming)

constexpr sink    CIN  = 0;
constexpr sink    COUT = 1;
constexpr sink    CERR = 2;

[[noreturn]] void exit(exitc c) noexcept;

err               write(sink s, strv v) noexcept;

} // namespace sys
} // namespace srr

#endif // SRR_SYS_HPP_
