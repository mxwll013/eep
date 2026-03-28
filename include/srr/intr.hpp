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

#ifndef SRR_INTR_HPP_
#define SRR_INTR_HPP_

#include "srr/types.hpp"

inline namespace srr {
namespace intr {

// NOLINTBEGIN(readability-identifier-naming)

template<typename T> struct is_triv_cp;
template<typename T> struct is_triv_ds;
template<typename T> struct is_triv_eq;

template<typename T> constexpr bool is_triv_cp_v = is_triv_cp<T>::val;
template<typename T> constexpr bool is_triv_ds_v = is_triv_ds<T>::val;
template<typename T> constexpr bool is_triv_eq_v = is_triv_eq<T>::val;

[[nodiscard]] constexpr u32         clz(u32 v) noexcept;
[[nodiscard]] constexpr u32         clz(u64 v) noexcept;
[[nodiscard]] constexpr u32         clz(usz v) noexcept;

// === impl ===

template<typename T> struct is_triv_cp {
    static constexpr bool val = __is_trivially_copyable(T);
};

template<typename T> struct is_triv_ds {
    static constexpr bool val = __is_trivially_destructible(T);
};

template<typename T> struct is_triv_eq {
    static constexpr bool val = __is_trivially_equality_comparable(T);
};

constexpr u32 clz(u32 v) noexcept { return static_cast<u32>(__builtin_clz(v)); }

constexpr u32 clz(u64 v) noexcept {
    return static_cast<u32>(__builtin_clzll(v));
}

constexpr u32 clz(usz v) noexcept {
    return static_cast<u32>(__builtin_clzl(v));
}

// NOLINTEND(readability-identifier-naming)

} // namespace intr
} // namespace srr

#endif // SRR_INTR_HPP_
