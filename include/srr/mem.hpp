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

#ifndef SRR_MEM_HPP_
#define SRR_MEM_HPP_

#include "srr/impl/Alloc.hpp"

#include "srr/alg.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

void *operator new(usz n, void *p) noexcept;
void  operator delete(void *p, void *q) noexcept;

inline namespace srr {
namespace mem {

// NOLINTBEGIN(readability-identifier-naming)

template<typename A>
concept Alloc                         = impl::Alloc<A>;

using sys_alloc                       = impl::SysAlloc;

template<typename T> using base_alloc = impl::BaseAlloc<T>;

// NOLINTEND(readability-identifier-naming)

template<typename T> T             *alloc(usz n) noexcept;
template<typename T> T             *alloc() noexcept;
template<typename T> void           dealloc(T *ptr, usz n) noexcept;
template<typename T> void           dealloc(T *ptr) noexcept;

template<typename T> constexpr void destroy(T *ptr) noexcept;
template<typename T, typename... U>
constexpr void construct(T *ptr, U &&...args) noexcept;

template<typename T>
constexpr bool cmpe(const T *dst, const T *src, usz n) noexcept;

template<typename T>
constexpr usz copye(T *dst, const T *src, usz d, usz s) noexcept;

template<typename T>
constexpr usz movee(T *dst, const T *src, usz d, usz s) noexcept;

template<typename T> constexpr void clse(T *dst, usz n) noexcept;

bool                    eq(const void *a, const void *b, usz n) noexcept;
void                    copy(void *dst, const void *src, usz n) noexcept;
void                    move(void *dst, const void *src, usz n) noexcept;
void                    set(void *dst, byte v, usz n) noexcept;
void                    zero(void *dst, usz n) noexcept;

// === impl ===

template<typename T> T *alloc(usz n) noexcept {
    return static_cast<T *>(sys_alloc::alloc(sizeof(T) * n));
}

template<typename T> T *alloc() noexcept {
    return static_cast<T *>(sys_alloc::alloc(sizeof(T)));
}

template<typename T> void dealloc(T *ptr, usz n) noexcept {
    sys_alloc::dealloc(ptr, sizeof(T) * n);
}

template<typename T> void dealloc(T *ptr) noexcept {
    sys_alloc::dealloc(ptr, sizeof(T));
}

template<typename T> constexpr void destroy(T *ptr) noexcept { ptr->~T(); }

template<typename T, typename... U>
constexpr void construct(T *ptr, U &&...args) noexcept {
    new (ptr) T{ fwd<U>(args)... };
}

template<typename T>
constexpr bool cmpe(const T *dst, const T *src, usz n) noexcept {
    if constexpr (is_triv_eq_v<T>)
        return eq(dst, src, n * sizeof(T));
    else
        for (usz i = 0; i < n; ++i)
            if (dst[i] != src[i]) return false;

    return true;
}

template<typename T>
constexpr usz copye(T *dst, const T *src, usz d, usz s) noexcept {
    const usz n = alg::min(d, s);

    if constexpr (is_triv_cp_v<T>)
        copy(dst, src, n * sizeof(T));
    else
        for (usz i = 0; i < n; ++i) construct(dst + i, src[i]);

    return n;
}

template<typename T>
constexpr usz movee(T *dst, const T *src, usz d, usz s) noexcept {
    const usz n = alg::min(d, s);

    if constexpr (is_triv_cp_v<T>)
        move(dst, src, n * sizeof(T));
    else
        for (usz i = 0; i < n; ++i) construct(dst + i, mv(src[i]));

    return n;
}

template<typename T> constexpr void clse(T *dst, usz n) noexcept {
    if constexpr (is_triv_ds_v<T>) return;

    for (usz i = 0; i < n; ++i) destroy(dst + i);
}

} // namespace mem
} // namespace srr

#endif // SRR_MEM_HPP_
