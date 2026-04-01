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

#include "srr/bit.hpp"
#include "srr/err.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace sys {

namespace {

namespace api {

[[nodiscard]] constexpr int cast(prot f) noexcept;
[[nodiscard]] constexpr int cast(map f) noexcept;

[[nodiscard]] errc          error() noexcept;
[[nodiscard]] bool          mapFail(void *p) noexcept;

[[nodiscard]] isz           write(int fd, const void *buf, usz len) noexcept;
[[nodiscard]] isz           read(int fd, void *buf, usz len) noexcept;
[[nodiscard]] void         *mmap(void *addr,
                                 usz   len,
                                 int   prot,
                                 int   flags,
                                 fd    f,
                                 isz   off) noexcept;
[[nodiscard]] int           munmap(void *addr, usz len) noexcept;
[[noreturn]] void           exit(int status) noexcept;

} // namespace api

// NOLINTNEXTLINE(readability-use-concise-preprocessor-directives)
#if defined(SRR_SYS_USE_LIBC)

namespace libc {

    #include <sys/mman.h>
    #include <unistd.h>

    #include <cerrno>

} // namespace libc

namespace api {

constexpr int cast(prot f) noexcept {
    uint r = 0;

    if (bit::has(f, prot::READ)) r |= PROT_READ;
    if (bit::has(f, prot::WRITE)) r |= PROT_WRITE;
    if (bit::has(f, prot::EXEC)) r |= PROT_EXEC;

    return static_cast<int>(r);
}

constexpr int cast(map f) noexcept {
    uint r = 0;

    if (bit::has(f, map::SHARED)) r |= MAP_SHARED;
    if (bit::has(f, map::PRIVATE)) r |= MAP_PRIVATE;
    if (bit::has(f, map::ANON)) r |= MAP_ANONYMOUS;

    return static_cast<int>(r);
}

errc error() noexcept {
    using namespace libc;

    switch (errno) {
    #if EWOULDBLOCK != EAGAIN
    case EWOULDBLOCK: [[fallthrough]];
    #endif
    case EAGAIN: return err::SYS_AGAIN;
    case EINTR : return err::SYS_INTER;
    case EINVAL: return err::SYS_BAD_ARG;
    case EBADF : return err::SYS_BAD_FD;
    case EFAULT: return err::SYS_BAD_ADDR;
    case ENOSPC: return err::SYS_NO_SPACE;
    case ENOMEM: return err::SYS_NO_MEM;
    case EFBIG : return err::SYS_LARGE_FILE;
    case ENFILE: [[fallthrough]];
    case EMFILE: return err::SYS_TOO_MANY_FILES;
    case EACCES: return err::SYS_ACCESS;
    case EPERM : return err::SYS_PERM;
    case EIO   : return err::SYS_IO;
    case EPIPE : return err::SYS_PIPE;
    default    : return err::SYS_FAIL;
    }
}

bool mapFail(void *p) noexcept { return p == MAP_FAILED; }

isz  write(int fd, const void *buf, usz len) noexcept {
    return libc::write(fd, buf, len);
}

isz read(int fd, void *buf, usz len) noexcept {
    return libc::read(fd, buf, len);
}

void *mmap(void *addr, usz len, int prot, int flags, fd f, isz off) noexcept {
    return libc::mmap(addr, len, prot, flags, f.val, off);
}

int  munmap(void *addr, usz len) noexcept { return libc::munmap(addr, len); }

void exit(int status) noexcept { libc::_exit(status); }

} // namespace api

#elif defined(SRR_SYS_USE_ASM)
    #error "ASM backend is not implemented yet"
#else
    #error "Unknown system backend"
#endif

} // namespace

res<usz> write(fd out, strv v) noexcept {
    const isz n = api::write(out.val, v.data(), v.len());

    if (n < 0) return api::error();

    return static_cast<usz>(n);
}

res<usz> read(fd in, strb b) noexcept {
    const isz n = api::read(in.val, b.data(), b.len());

    if (n < 0) return api::error();

    return static_cast<usz>(n);
}

res<void *> mmap(void *addr, usz len) noexcept {
    return mmap(addr, len, prot::RW, map::PRIV_ANON, { -1 }, 0);
}

res<void *> mmap(void *addr,
                 usz   len,
                 prot  prot,
                 map   flags,
                 fd    f,
                 isz   off) noexcept {
    void *p = api::mmap(addr, len, api::cast(prot), api::cast(flags), f, off);

    if (api::mapFail(p)) return api::error();

    return p;
}

err munmap(void *addr, usz len) noexcept {
    const int r = api::munmap(addr, len);

    if (r < 0) return api::error();

    return {};
}

void exit() noexcept { api::exit(0); }

void exit(err e) noexcept { api::exit(static_cast<int>(e.ter().code())); }

void exit(ter e) noexcept { api::exit(static_cast<int>(e.code())); }

} // namespace sys
} // namespace srr
