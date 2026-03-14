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

#include "srr/alg.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

#define SRR_KB(...) (1024 * (__VA_ARGS__))
#define SRR_MB(...) (1024 * SRR_KB(__VA_ARGS__))
#define SRR_GB(...) (1024 * SRR_MB(__VA_ARGS__))

void *operator new(usize n, void *p) noexcept;
void  operator delete(void *p, void *q) noexcept;

inline namespace srr {
namespace mem {

template<typename T, typename... U>
constexpr void                      build(T *ptr, U &&...args) noexcept;
template<typename T> constexpr void destroy(T *ptr) noexcept;

template<typename T>
constexpr usize copye(T *dst, const T *src, usize d, usize s) noexcept;

void            copy(void *dst, const void *src, usize n) noexcept;
void            move(void *dst, const void *src, usize n) noexcept;
void            set(void *dst, byte v, usize n) noexcept;
void            zero(void *dst, usize n) noexcept;

// === impl ===

template<typename T, typename... U>
constexpr void build(T *ptr, U &&...args) noexcept {
    new (ptr) T{ fwd<U>(args)... };
}

template<typename T> constexpr void destroy(T *ptr) noexcept { ptr->~T(); }

template<typename T>
constexpr usize copye(T *dst, const T *src, usize d, usize s) noexcept {
    const usize n = alg::min(d, s);

    if constexpr (is_triv_cp_v<T>)
        copy(dst, src, n * sizeof(T));
    else
        for (usize i = 0; i < n; ++i) build(dst + i, src[i]);

    return n;
}

} // namespace mem
} // namespace srr

#endif // SRR_MEM_HPP_
