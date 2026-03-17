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

#ifndef SRR_ALG_HPP_
#define SRR_ALG_HPP_

#include "srr/intr.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace alg {

// NOLINTBEGIN(readability-identifier-naming)

template<typename T> [[nodiscard]] constexpr T min(T a, T b) noexcept;
template<typename T> [[nodiscard]] constexpr T max(T a, T b) noexcept;
template<typename T> [[nodiscard]] constexpr T clamp(T v, T lo, T hi) noexcept;

[[nodiscard]] constexpr usize                  ceil_log2(usize v) noexcept;
[[nodiscard]] constexpr usize                  ceil_pow2(usize v) noexcept;

// NOLINTEND(readability-identifier-naming)

// === impl ===

template<typename T> constexpr T               min(T a, T b) noexcept {
    return a < b ? a : b;
}

template<typename T> constexpr T max(T a, T b) noexcept {
    return a > b ? a : b;
}

template<typename T> constexpr T clamp(T v, T lo, T hi) noexcept {
    return min(max(v, lo), hi);
}

constexpr usize ceil_log2(usize v) noexcept {
    if (v <= 1) return 0;

    return (sizeof(usize) * 8) - intr::clz(v - 1);
}

constexpr usize ceil_pow2(usize v) noexcept { return 1_usz << ceil_log2(v); }

} // namespace alg
} // namespace srr

#endif // SRR_ALG_HPP_
