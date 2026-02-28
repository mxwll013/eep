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

#ifndef SRR_TRAITS_HPP_
#define SRR_TRAITS_HPP_

#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

template<typename T>
struct rm_ref;

template<typename T>
struct is_lvalue_ref;

template<usize N, typename... U>
struct is_len;

template<typename T>
using rm_ref_t = typename rm_ref<T>::type;

template<typename T>
constexpr bool is_lvalue_ref_v = is_lvalue_ref<T>::val;

template<usize N, typename... U>
constexpr bool is_len_v = is_len<N, U...>::val;

template<typename T>
[[nodiscard]] constexpr T &&fwd(rm_ref_t<T> &t) noexcept;
template<typename T>
[[nodiscard]] constexpr T &&fwd(rm_ref_t<T> &&t) noexcept;

// === impl ===

template<typename T>
struct rm_ref {
    using type = T;
};

template<typename T>
struct rm_ref<T &> {
    using type = T;
};

template<typename T>
struct rm_ref<T &&> {
    using type = T;
};

template<typename T>
struct is_lvalue_ref {
    static constexpr bool val = false;
};

template<typename T>
struct is_lvalue_ref<T &> {
    static constexpr bool val = true;
};

template<usize N, typename... U>
struct is_len {
    static constexpr bool val = sizeof...(U) == N;
};

template<typename T>
constexpr T &&fwd(rm_ref_t<T> &t) noexcept {
    return static_cast<T &&>(t);
}

template<typename T>
constexpr T &&fwd(rm_ref_t<T> &&t) noexcept {
    static_assert(!is_lvalue_ref_v<T>,
                  "lvalue reference cannot be forwarded as rvalue");
    return static_cast<T &&>(t);
}

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_TRAITS_HPP_
