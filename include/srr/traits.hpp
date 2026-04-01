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

#include "srr/impl/lang.hpp"
#include "srr/impl/traits.hpp"

#include "srr/intr.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

template<usz... U> using idx_seq               = impl::idx_seq<U...>;

template<typename T> using no_deduce_t         = impl::no_deduce_t<T>;

template<typename T> using rm_ref_t            = impl::rm_ref_t<T>;
template<typename T> using rm_c_t              = impl::rm_c_t<T>;
template<typename T> using rm_v_t              = impl::rm_v_t<T>;
template<typename T> using rm_cv_t             = impl::rm_cv_t<T>;

template<typename T> using mk_u_t              = impl::mk_u_t<T>;
template<usz N> using mk_idx_seq_t             = impl::mk_idx_seq_t<N>;
template<typename... U> using mk_idx_seq_for_t = impl::mk_idx_seq_for_t<U...>;

template<typename T> using val_t               = impl::val_t<T>;
template<typename T> using alloc_t             = impl::alloc_t<T>;
template<typename T> using alias_t             = impl::alias_t<T>;

template<usz N, typename... U>
constexpr bool is_len_v = impl::is_len_v<N, U...>;

template<typename T, typename U>
constexpr bool                      is_same_v     = impl::is_same_v<T, U>;

template<typename T> constexpr bool is_lval_ref_v = impl::is_lval_ref_v<T>;
template<typename T> constexpr bool is_s_v        = impl::is_s_v<T>;
template<typename T> constexpr bool is_u_v        = impl::is_u_v<T>;

template<typename T> using under_t                = intr::under_t<T>;

template<typename T> constexpr bool is_int_v      = intr::is_int_v<T>;
template<typename T> constexpr bool is_triv_cp_v  = intr::is_triv_cp_v<T>;
template<typename T> constexpr bool is_triv_ds_v  = intr::is_triv_ds_v<T>;
template<typename T> constexpr bool is_triv_eq_v  = intr::is_triv_eq_v<T>;

template<typename T, typename U>
concept Same = is_same_v<T, U> && is_same_v<U, T>;

template<typename T> constexpr T           &&fwd(rm_ref_t<T> &t) noexcept;
template<typename T> constexpr T           &&fwd(rm_ref_t<T> &&t) noexcept;
template<typename T> constexpr rm_ref_t<T> &&mv(T &&t) noexcept;

// === impl ===

template<typename T> constexpr T           &&fwd(rm_ref_t<T> &t) noexcept {
    return static_cast<T &&>(t);
}

template<typename T> constexpr T &&fwd(rm_ref_t<T> &&t) noexcept {
    static_assert(!is_lval_ref_v<T>);
    return static_cast<T &&>(t);
}

template<typename T> constexpr rm_ref_t<T> &&mv(T &&t) noexcept {
    return static_cast<rm_ref_t<T> &&>(t);
}

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_TRAITS_HPP_
