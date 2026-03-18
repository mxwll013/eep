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

struct Conf;

// NOLINTBEGIN(readability-identifier-naming)

// Sink (output stream)
using sink                    = u32;
using conf                    = Conf;


// NOLINTEND(readability-identifier-naming)

constexpr sink      CIN       = 0;
constexpr sink      COUT      = 1;
constexpr sink      CERR      = 2;

constexpr usz       PAGE_SIZE = 4096;

err                 write(sink s, strv v) noexcept;

[[nodiscard]] void *mmap(usz len) noexcept;
err                 munmap(void *ptr, usz len) noexcept;

[[noreturn]] void   exit(exitc c) noexcept;

} // namespace sys
} // namespace srr

#endif // SRR_SYS_HPP_
