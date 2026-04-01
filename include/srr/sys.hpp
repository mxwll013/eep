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

#if defined(BRV_FORCE_LIBC)
    #define SRR_SYS_USE_LIBC 1
#elif defined(__linux__)
    #define SRR_SYS_LINUX   1
    #define SRR_SYS_USE_ASM 1
#elif defined(__APPLE__)
    #define SRR_SYS_DARWIN   1
    #define SRR_SYS_USE_LIBC 1
#else
    #error "Unsupported platform"
#endif

inline namespace srr {
namespace sys {

// NOLINTBEGIN(readability-identifier-naming)

using fd   = struct Fd;
using prot = enum class ProtFlags : u8;
using map  = enum class MapFlags : u8;

// NOLINTEND(readability-identifier-naming)

struct Fd {
    int val;
};

enum class ProtFlags : u8 {
    NONE  = 0x00,
    READ  = 0x01,
    WRITE = 0x02,
    EXEC  = 0x04,

    RW    = READ | WRITE,
    ALL   = RW | EXEC,
};

enum class MapFlags : u8 {
    SHARED    = 0x01,
    PRIVATE   = 0x02,
    ANON      = 0x04,

    PRIV_ANON = PRIVATE | ANON,
};

constexpr fd              CIN       = { 0 };
constexpr fd              COUT      = { 1 };
constexpr fd              CERR      = { 2 };

constexpr usz             PAGE_SIZE = 4096;

res<usz>                  write(fd out, strv v) noexcept;
res<usz>                  read(fd in, strb b) noexcept;

[[nodiscard]] res<void *> mmap(void *addr, usz len) noexcept;
[[nodiscard]] res<void *> mmap(void *addr,
                               usz   len,
                               prot  prot,
                               map   flags,
                               fd    f,
                               isz   off) noexcept;
[[nodiscard]] err         munmap(void *addr, usz len) noexcept;

[[noreturn]] void         exit() noexcept;
[[noreturn]] void         exit(err e) noexcept;
[[noreturn]] void         exit(ter e) noexcept;

// === impl ===

} // namespace sys
} // namespace srr

#endif // SRR_SYS_HPP_
