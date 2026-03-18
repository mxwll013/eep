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

template<typename T> constexpr bool TRIV_CP = __is_trivially_copyable(T);
template<typename T> constexpr bool TRIV_DS = __is_trivially_destructible(T);
template<typename T>
constexpr bool              TRIV_EQ = __is_trivially_equality_comparable(T);

[[nodiscard]] constexpr u32 clz(u32 v) noexcept;
[[nodiscard]] constexpr u32 clz(u64 v) noexcept;
[[nodiscard]] constexpr u32 clz(usz v) noexcept;

// === impl ===

constexpr u32 clz(u32 v) noexcept { return static_cast<u32>(__builtin_clz(v)); }

constexpr u32 clz(u64 v) noexcept {
    return static_cast<u32>(__builtin_clzll(v));
}

constexpr u32 clz(usz v) noexcept {
    return static_cast<u32>(__builtin_clzl(v));
}

} // namespace intr
} // namespace srr

#endif // SRR_INTR_HPP_
