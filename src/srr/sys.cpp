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

#include <sys/mman.h>
#include <unistd.h>

inline namespace srr {
namespace sys {

err write(sink s, strv v) noexcept {
    const isz w = ::write(static_cast<int>(s), v.data(), v.len());

    if (w < 0) return err::SYS_WRITE_FAIL;

    return {};
}

void *mmap(usz len) noexcept {
    const usz pages = (len + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);

    return ::mmap(nullptr,
                  pages,
                  PROT_READ | PROT_WRITE,
                  MAP_ANONYMOUS | MAP_PRIVATE,
                  -1,
                  0);
}

err munmap(void *ptr, usz len) noexcept {
    const int r = ::munmap(ptr, len);

    if (r < 0) return err::SYS_MUNMAP_FAIL;

    return {};
}

void exit(terc c) noexcept { ::_exit(static_cast<int>(c)); }

} // namespace sys
} // namespace srr
