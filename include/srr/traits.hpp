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

template<bool B> struct bool_constant;

using true_t  = bool_constant<true>;
using false_t = bool_constant<false>;

template<typename T, typename U> struct is_same;
template<typename T> struct no_deduce;
template<typename T> struct is_int;
template<typename T> struct is_signed;
template<typename T> struct make_unsigned;
template<typename T> struct rm_ref;
template<typename T> struct is_lvalue_ref;

template<usize N, typename... U> struct is_len;

template<typename T> using no_deduce_t     = typename no_deduce<T>::type;
template<typename T> using make_unsigned_t = typename make_unsigned<T>::type;
template<typename T> using rm_ref_t        = typename rm_ref<T>::type;

template<typename T, typename U> constexpr bool is_same_v = is_same<T, U>::val;
template<typename T> constexpr bool             is_int_v  = is_int<T>::val;
template<typename T> constexpr bool             is_signed_v = is_signed<T>::val;
template<typename T> constexpr bool is_lvalue_ref_v = is_lvalue_ref<T>::val;

template<usize N, typename... U> constexpr bool is_len_v = is_len<N, U...>::val;

template<typename T, typename U>
concept Same = is_same_v<T, U> && is_same_v<U, T>;

template<typename T>
concept Int = is_int_v<T>;

template<typename T>
concept SignedInt = is_int_v<T> && is_signed_v<T>;

template<typename T>
concept UnsignedInt = is_int_v<T> && !is_signed_v<T>;

template<typename T> constexpr T &&fwd(rm_ref_t<T> &t) noexcept;
template<typename T> constexpr T &&fwd(rm_ref_t<T> &&t) noexcept;

// === impl ===

template<bool B> struct bool_constant {
    static constexpr bool val = B;
};

template<typename T, typename U> struct is_same : false_t {};

template<typename T> struct is_same<T, T> : true_t {};

template<typename T> struct no_deduce {
    using type = T;
};

template<typename> struct is_int : false_t {};

template<> struct is_int<i8> : true_t {};

template<> struct is_int<i16> : true_t {};

template<> struct is_int<i32> : true_t {};

template<> struct is_int<i64> : true_t {};

template<> struct is_int<u8> : true_t {};

template<> struct is_int<u16> : true_t {};

template<> struct is_int<u32> : true_t {};

template<> struct is_int<u64> : true_t {};

template<typename> struct is_signed : false_t {};

template<> struct is_signed<i8> : true_t {};

template<> struct is_signed<i16> : true_t {};

template<> struct is_signed<i32> : true_t {};

template<> struct is_signed<i64> : true_t {};

template<typename T> struct make_unsigned {
    using type = T;
};

template<> struct make_unsigned<i8> {
    using type = u8;
};

template<> struct make_unsigned<i16> {
    using type = u16;
};

template<> struct make_unsigned<i32> {
    using type = u32;
};

template<> struct make_unsigned<i64> {
    using type = u64;
};

template<typename T> struct rm_ref {
    using type = T;
};

template<typename T> struct rm_ref<T &> {
    using type = T;
};

template<typename T> struct rm_ref<T &&> {
    using type = T;
};

template<typename T> struct is_lvalue_ref {
    static constexpr bool val = false;
};

template<typename T> struct is_lvalue_ref<T &> {
    static constexpr bool val = true;
};

template<usize N, typename... U> struct is_len {
    static constexpr bool val = sizeof...(U) == N;
};

template<typename T> constexpr T &&fwd(rm_ref_t<T> &t) noexcept {
    return static_cast<T &&>(t);
}

template<typename T> constexpr T &&fwd(rm_ref_t<T> &&t) noexcept {
    static_assert(!is_lvalue_ref_v<T>,
                  "lvalue reference cannot be forwarded as rvalue");
    return static_cast<T &&>(t);
}

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_TRAITS_HPP_
