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

#include "srr/intr.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

template<bool B> struct bool_k;

using true_t  = bool_k<true>;
using false_t = bool_k<false>;

template<bool C, typename T, typename U> struct if_;

template<typename T, typename U> struct is_same;
template<usize N, typename... U> struct is_len;

template<typename T> struct is_triv_cp;
template<typename T> struct is_triv_ds;
template<typename T> struct is_int;
template<typename T> struct is_signed;
template<typename T> struct is_lvalue_ref;
template<typename T> struct is_arr;
template<typename T> struct is_fn;

template<typename T> struct no_deduce;
template<typename T> struct clean;
template<typename T> struct decay;

template<typename T> struct rm_ref;
template<typename T> struct rm_ext;
template<typename T> struct rm_c;
template<typename T> struct rm_v;
template<typename T> struct rm_cv;

template<typename T> struct make_unsigned;

template<typename T> struct val;
template<typename T> struct ptr;
template<typename T> struct arr_ptr;

template<typename T> using no_deduce_t     = typename no_deduce<T>::type;
template<typename T> using clean_t         = typename clean<T>::type;
template<typename T> using decay_t         = typename decay<T>::type;

template<typename T> using rm_ref_t        = typename rm_ref<T>::type;
template<typename T> using rm_ext_t        = typename rm_ext<T>::type;
template<typename T> using rm_c_t          = typename rm_c<T>::type;
template<typename T> using rm_v_t          = typename rm_v<T>::type;
template<typename T> using rm_cv_t         = typename rm_cv<T>::type;

template<typename T> using make_unsigned_t = typename make_unsigned<T>::type;

template<typename T> using val_t           = typename val<T>::type;
template<typename T> using ptr_t           = typename ptr<T>::type;
template<typename T> using arr_ptr_t       = typename arr_ptr<T>::type;

template<bool C, typename T, typename U>
using if_t = typename if_<C, T, U>::type;

template<typename T, typename U> constexpr bool is_same_v = is_same<T, U>::val;
template<usize N, typename... U> constexpr bool is_len_v = is_len<N, U...>::val;

template<typename T> constexpr bool is_triv_cp_v         = is_triv_cp<T>::val;
template<typename T> constexpr bool is_triv_ds_v         = is_triv_ds<T>::val;
template<typename T> constexpr bool is_int_v             = is_int<T>::val;
template<typename T> constexpr bool is_signed_v          = is_signed<T>::val;
template<typename T> constexpr bool is_lvalue_ref_v = is_lvalue_ref<T>::val;
template<typename T> constexpr bool is_arr_v        = is_arr<T>::val;
template<typename T> constexpr bool is_fn_v         = is_fn<T>::val;

template<typename T, typename U>
concept Same = is_same_v<T, U> && is_same_v<U, T>;

template<typename T>
concept Int = is_int_v<T>;

template<typename T>
concept SignedInt = is_int_v<T> && is_signed_v<T>;

template<typename T>
concept UnsignedInt = is_int_v<T> && !is_signed_v<T>;

template<typename T> constexpr T           &&fwd(rm_ref_t<T> &t) noexcept;
template<typename T> constexpr T           &&fwd(rm_ref_t<T> &&t) noexcept;
template<typename T> constexpr rm_ref_t<T> &&mv(T &&t) noexcept;

// === impl ===

template<bool B> struct bool_k {
    static constexpr bool val = B;
};

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

template<typename T> struct decay {
    using U = rm_ref_t<T>;

    using type =
        rm_cv_t<if_t<is_arr_v<U>, arr_ptr<U>, if_t<is_fn_v<U>, ptr_t<U>, U>>>;
};

template<typename T> struct is_triv_cp {
    static constexpr bool val = intr::TRIV_CP<T>;
};

template<typename T> struct is_triv_ds {
    static constexpr bool val = intr::TRIV_DS<T>;
};

template<typename> struct is_int : false_t {};

template<> struct is_int<i8> : true_t {};

template<> struct is_int<i16> : true_t {};

template<> struct is_int<i32> : true_t {};

template<> struct is_int<i64> : true_t {};

template<> struct is_int<isize> : true_t {};

template<> struct is_int<u8> : true_t {};

template<> struct is_int<u16> : true_t {};

template<> struct is_int<u32> : true_t {};

template<> struct is_int<u64> : true_t {};

template<> struct is_int<usize> : true_t {};

template<typename> struct is_signed : false_t {};

template<> struct is_signed<i8> : true_t {};

template<> struct is_signed<i16> : true_t {};

template<> struct is_signed<i32> : true_t {};

template<> struct is_signed<i64> : true_t {};

template<> struct is_signed<isize> : true_t {};

template<typename T> struct is_lvalue_ref {
    static constexpr bool val = false;
};

template<typename T> struct is_lvalue_ref<T &> {
    static constexpr bool val = true;
};

template<typename T> struct is_arr : false_t {};

template<typename T> struct is_arr<T[]> : true_t {};

template<typename T, usize N> struct is_arr<T[N]> : true_t {};

template<typename T> struct is_fn : false_t {};

template<typename T, typename... U> struct is_fn<T(U...)> : true_t {};

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

template<typename T> struct rm_ext {
    using type = T;
};

template<typename T> struct rm_ext<T[]> {
    using type = T;
};

template<typename T, usize N> struct rm_ext<T[N]> {
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

template<typename T> struct val {
    using type = T::val_t;
};

template<typename T> struct ptr {
    using type = T *;
};

template<typename T> struct arr_ptr {
    using type = rm_ext_t<T> *;
};

template<usize N, typename... U> struct is_len {
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
