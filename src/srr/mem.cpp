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

#include "srr/mem.hpp"

#include "srr/types.hpp"

void *operator new([[maybe_unused]] usz n, void *p) noexcept { return p; }

void  operator delete([[maybe_unused]] void *p,
                     [[maybe_unused]] void *q) noexcept {}

inline namespace srr {
namespace mem {

bool eq(const void *a, const void *b, usz n) noexcept {
    const byte *x = static_cast<const byte *>(a);
    const byte *y = static_cast<const byte *>(b);

    for (usz i = 0; i < n; ++i)
        if (x[i] != y[i]) return false;

    return true;
}

void copy(void *dst, const void *src, usz n) noexcept {
    byte       *d = static_cast<byte *>(dst);
    const byte *s = static_cast<const byte *>(src);

    for (usz i = 0; i < n; ++i) d[i] = s[i];
}

void move(void *dst, const void *src, usz n) noexcept {
    if (dst < src) {
        copy(dst, src, n);
        return;
    }


    // NOLINTNEXTLINE(misc-const-correctness)
    byte       *d = static_cast<byte *>(dst) + n;
    const byte *s = static_cast<const byte *>(src) + n;

    for (usz i = 0; i < n; ++i) *--d = *--s;
}

void set(void *dst, byte v, usz n) noexcept {
    byte *d = static_cast<byte *>(dst);

    for (usz i = 0; i < n; ++i) d[i] = v;
}

void zero(void *dst, usz n) noexcept { set(dst, 0, n); }

} // namespace mem
} // namespace srr
