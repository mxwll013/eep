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

#ifndef SRR_BIT_HPP_
#define SRR_BIT_HPP_

#include "srr/intr.hpp"

inline namespace srr {
namespace bit {

template<typename T>
[[nodiscard]] constexpr intr::under_t<T> under(T v) noexcept {
    return static_cast<intr::under_t<T>>(v);
}

template<typename T> constexpr void set(T &f, T v) noexcept {
    f = under(f) | under(v);
}

template<typename T> [[nodiscard]] constexpr bool has(T f, T q) noexcept {
    return (under(f) & under(q)) != 0;
}

} // namespace bit
} // namespace srr

#endif // SRR_BIT_HPP_
