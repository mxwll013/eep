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

using true_t  = bool_k<true>;
using false_t = bool_k<false>;

template<bool C, typename T, typename U> struct if_;

template<typename T, typename U> struct is_same;
template<usz N, typename... U> struct is_len;

template<typename T> struct is_lvalue_ref;
template<typename T> struct is_arr;
template<typename T> struct is_fn;

template<typename T> struct no_deduce;
template<typename T> struct clean;

template<typename T> struct rm_ref;
template<typename T> struct rm_ext;
template<typename T> struct rm_c;
template<typename T> struct rm_v;
template<typename T> struct rm_cv;

template<typename T> struct mk_u;

template<typename T> struct val;
template<typename T> struct alloc;
template<typename T> struct alias;

template<typename T> using no_deduce_t = typename no_deduce<T>::type;
template<typename T> using clean_t     = typename clean<T>::type;

template<typename T> using rm_ref_t    = typename rm_ref<T>::type;
template<typename T> using rm_ext_t    = typename rm_ext<T>::type;
template<typename T> using rm_c_t      = typename rm_c<T>::type;
template<typename T> using rm_v_t      = typename rm_v<T>::type;
template<typename T> using rm_cv_t     = typename rm_cv<T>::type;

template<typename T> using mk_u_t      = typename mk_u<T>::type;

template<typename T> using val_t       = typename val<T>::type;
template<typename T> using alloc_t     = typename alloc<T>::type;
template<typename T> using alias_t     = typename alias<T>::type;

template<bool C, typename T, typename U>
using if_t = typename if_<C, T, U>::type;

template<typename T, typename U> constexpr bool is_same_v = is_same<T, U>::val;
template<usz N, typename... U> constexpr bool   is_len_v = is_len<N, U...>::val;

template<typename T> constexpr bool is_lvalue_ref_v = is_lvalue_ref<T>::val;
template<typename T> constexpr bool is_arr_v        = is_arr<T>::val;
template<typename T> constexpr bool is_fn_v         = is_fn<T>::val;

template<typename T, typename U>
concept Same = is_same_v<T, U> && is_same_v<U, T>;

template<typename T> constexpr T           &&fwd(rm_ref_t<T> &t) noexcept;
template<typename T> constexpr T           &&fwd(rm_ref_t<T> &&t) noexcept;
template<typename T> constexpr rm_ref_t<T> &&mv(T &&t) noexcept;

// === impl ===

template<bool C, typename T, typename U> struct if_ {
    using type = U;
};

template<typename T, typename U> struct if_<true, T, U> {
    using type = T;
};

template<typename T, typename U> struct is_same : false_t {};

template<typename T> struct is_same<T, T> : true_t {};

template<typename T> struct no_deduce {
    using type = T;
};

template<typename T> struct clean {
    using type = rm_cv_t<rm_ref_t<T>>;
};

template<typename T> struct is_lvalue_ref {
    static constexpr bool val = false;
};

template<typename T> struct is_lvalue_ref<T &> {
    static constexpr bool val = true;
};

template<typename T> struct is_arr : false_t {};

template<typename T> struct is_arr<T[]> : true_t {};

template<typename T, usz N> struct is_arr<T[N]> : true_t {};

template<typename T> struct is_fn : false_t {};

template<typename T, typename... U> struct is_fn<T(U...)> : true_t {};

template<typename T> struct rm_ref {
    using type = T;
};

template<typename T> struct rm_ref<T &> {
    using type = T;
};

template<typename T> struct rm_ref<T &&> {
    using type = T;
};

template<typename T> struct rm_ext {
    using type = T;
};

template<typename T> struct rm_ext<T[]> {
    using type = T;
};

template<typename T, usz N> struct rm_ext<T[N]> {
    using type = T;
};

template<typename T> struct rm_c {
    using type = T;
};

template<typename T> struct rm_c<const T> {
    using type = T;
};

template<typename T> struct rm_v {
    using type = T;
};

template<typename T> struct rm_v<volatile T> {
    using type = T;
};

template<typename T> struct rm_cv {
    using type = rm_v_t<rm_c_t<T>>;
};

template<typename T> struct mk_u {
    using type = T;
};

template<> struct mk_u<sbyte> {
    using type = ubyte;
};

template<> struct mk_u<sshort> {
    using type = ushort;
};

template<> struct mk_u<sint> {
    using type = uint;
};

template<> struct mk_u<slong> {
    using type = ulong;
};

template<> struct mk_u<sll> {
    using type = ull;
};

template<typename T> struct val {
    using type = T::val_t;
};

template<typename T> struct alloc {
    using type = T::alloc_t;
};

template<typename T> struct alias {
    using type = T::alias_t;
};

template<usz N, typename... U> struct is_len {
    static constexpr bool val = sizeof...(U) == N;
};

template<typename T> constexpr T &&fwd(rm_ref_t<T> &t) noexcept {
    return static_cast<T &&>(t);
}

template<typename T> constexpr T &&fwd(rm_ref_t<T> &&t) noexcept {
    static_assert(!is_lvalue_ref_v<T>);
    return static_cast<T &&>(t);
}

template<typename T> constexpr rm_ref_t<T> &&mv(T &&t) noexcept {
    return static_cast<rm_ref_t<T> &&>(t);
}


// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_TRAITS_HPP_
