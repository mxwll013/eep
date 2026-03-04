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

inline namespace srr {
namespace alg {

template<typename T>
[[nodiscard]] constexpr T min(T a, T b) noexcept;
template<typename T>
[[nodiscard]] constexpr T max(T a, T b) noexcept;
template<typename T>
[[nodiscard]] constexpr T clamp(T v, T lo, T hi) noexcept;

// === impl ===

template<typename T>
constexpr T min(T a, T b) noexcept {
    return a < b ? a : b;
}

template<typename T>
constexpr T max(T a, T b) noexcept {
    return a > b ? a : b;
}

template<typename T>
constexpr T clamp(T v, T lo, T hi) noexcept {
    return min(max(v, lo), hi);
}

} // namespace alg
} // namespace srr

#endif // SRR_ALG_HPP_
