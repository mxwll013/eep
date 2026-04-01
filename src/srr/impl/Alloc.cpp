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

#include "srr/impl/Alloc.hpp"

#include "srr/impl/FreeList.hpp"

#include "srr/alg.hpp"
#include "srr/err.hpp"
#include "srr/sys.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

namespace {

void *map(usz n) noexcept {
    const res<void *> r = sys::mmap(nullptr, n);
    if (r.bad()) sys::exit(r.err());
    return r.unwrap();
}

void unmap(void *p, usz len) noexcept {
    const err e = sys::munmap(p, len);
    if (e) sys::exit(e);
}

usz index(usz n) noexcept { return alg::ceil_log2(alg::max(n, sizeof(Block))); }

void *split(void *b, usz i) noexcept {
    return reinterpret_cast<byte *>(b) + (1_usz << i);
}

void *buddy(void *b, usz n) noexcept {
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    return reinterpret_cast<void *>(reinterpret_cast<usz>(b) ^ n);
}

} // namespace

FreeList SysAlloc::lists[SysAlloc::N] = {};

void    *SysAlloc::alloc(usz n) noexcept {
    if (n == 0) return nullptr;
    if (n > sys::PAGE_SIZE) return map(n);

    const usz k = index(n);
    n           = 1_usz << k;

    usz i       = k;
    while (i < N && lists[i].empty()) ++i;

    void *p = nullptr;

    if (i == N) {
        --i;
        p = map(1_usz << N);
    } else {
        p = lists[i].pop();
    }

    while (i > k) {
        --i;
        lists[i].push(split(p, i));
    }

    return p;
}

void SysAlloc::dealloc(void *ptr, usz n) noexcept {
    if (ptr == nullptr) return;
    if (n > sys::PAGE_SIZE) {
        unmap(ptr, n);
        return;
    }

    usz   k = index(n);
    void *b = ptr;

    while (k < N - 1) {
        n       = 1_usz << k;
        void *q = buddy(b, n);

        if (lists[k].pop(q) == nullptr) break;

        b = alg::min(b, q);
        ++k;
    }

    lists[k].push(b);
}

} // namespace impl
} // namespace srr
