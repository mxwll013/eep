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

#ifndef SRR_IMPL_LANG_HPP_
#define SRR_IMPL_LANG_HPP_

inline namespace srr {
namespace impl {
// NOLINTBEGIN(readability-identifier-naming)

template<typename T, typename U> struct is_same;

template<typename T> struct is_lval_ref;
template<typename T> struct is_s;
template<typename T> struct is_u;

template<typename T> struct no_deduce;

template<typename T, T C> struct type_k;

template<bool C, typename T, typename U> struct if_;

template<typename T> struct umax;
template<typename T> struct smin;
template<typename T> struct smax;
template<typename T> struct min;
template<typename T> struct max;

template<typename T> struct rm_ref;
template<typename T> struct rm_c;
template<typename T> struct rm_v;
template<typename T> struct rm_cv;

template<typename T> struct val;
template<typename T> struct alloc;
template<typename T> struct alias;

template<bool C, typename T, typename U>
using if_t                             = typename if_<C, T, U>::type;

template<typename T> using no_deduce_t = typename no_deduce<T>::type;

template<typename T> using rm_ref_t    = typename rm_ref<T>::type;
template<typename T> using rm_c_t      = typename rm_c<T>::type;
template<typename T> using rm_v_t      = typename rm_v<T>::type;
template<typename T> using rm_cv_t     = typename rm_cv<T>::type;

template<typename T> using val_t       = typename val<T>::type;
template<typename T> using alloc_t     = typename alloc<T>::type;
template<typename T> using alias_t     = typename alias<T>::type;

template<bool C> using bool_k          = type_k<bool, C>;

using true_t                           = bool_k<true>;
using false_t                          = bool_k<false>;

template<typename T> constexpr T                umax_v    = umax<T>::val;
template<typename T> constexpr T                smin_v    = smin<T>::val;
template<typename T> constexpr T                smax_v    = smax<T>::val;
template<typename T> constexpr T                min_v     = min<T>::val;
template<typename T> constexpr T                max_v     = max<T>::val;

template<typename T, typename U> constexpr bool is_same_v = is_same<T, U>::val;

template<typename T> constexpr bool is_lval_ref_v         = is_lval_ref<T>::val;
template<typename T> constexpr bool is_s_v                = is_s<T>::val;
template<typename T> constexpr bool is_u_v                = is_u<T>::val;

// === impl ===

template<typename T, typename U> struct is_same {
    static constexpr bool val = false;
};

template<typename T> struct no_deduce {
    using type = T;
};

template<typename T> struct is_same<T, T> {
    static constexpr bool val = true;
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

template<typename T> struct alloc {
    using type = T::alloc_t;
};

template<typename T>
concept Aliased = requires { typename T::alias_t; };

template<typename T> struct alias {
    using type = T;
};

template<Aliased T> struct alias<T> {
    using type = T::alias_t;
};

template<typename T, T C> struct type_k {
    static constexpr T val = C;
};

template<bool C, typename T, typename U> struct if_ {
    using type = U;
};

template<typename T, typename U> struct if_<true, T, U> {
    using type = T;
};

template<typename T> struct umax : type_k<T, static_cast<T>(-1)> {};

template<typename T>
// NOLINTNEXTLINE(hicpp-signed-bitwise)
struct smin : type_k<T, static_cast<T>(T{ 1 } << (sizeof(T) * 8 - 1))> {};

template<typename T>
// NOLINTNEXTLINE(hicpp-signed-bitwise)
struct smax : type_k<T, static_cast<T>(~(T{ 1 } << (sizeof(T) * 8 - 1)))> {};

template<typename T> struct is_lval_ref : bool_k<false> {};

template<typename T> struct is_lval_ref<T &> : bool_k<true> {};

template<typename T> struct is_s : bool_k < umax_v<T><0> {};

template<typename T> struct is_u : bool_k<0 < umax_v<T>> {};

template<typename T> struct min : type_k<T, is_s_v<T> ? smin_v<T> : 0> {};

template<typename T>
struct max : type_k<T, is_s_v<T> ? smax_v<T> : umax_v<T>> {};

// NOLINTEND(readability-identifier-naming)

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_LANG_HPP_
