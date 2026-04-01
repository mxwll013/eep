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

#ifndef SRR_IMPL_TRAITS_HPP_
#define SRR_IMPL_TRAITS_HPP_

#include "srr/types.hpp"

inline namespace srr {
namespace impl {
// NOLINTBEGIN(readability-identifier-naming)

template<typename T> struct mk_u;

template<usz N, usz... U> struct mk_idx_seq;

template<usz N, typename... U> struct is_len;

template<typename T> using mk_u_t = typename mk_u<T>::type;

template<usz... U> struct idx_seq {};

template<usz N> using mk_idx_seq_t = typename mk_idx_seq<N>::type;

template<typename... U>
using mk_idx_seq_for_t = typename mk_idx_seq<sizeof...(U)>::type;

template<usz N, typename... U> constexpr bool is_len_v = is_len<N, U...>::val;

// === impl ===

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

template<usz N, usz... U> struct mk_idx_seq : mk_idx_seq<N - 1, N - 1, U...> {};

template<usz... U> struct mk_idx_seq<0, U...> {
    using type = idx_seq<U...>;
};

template<usz N, typename... U> struct is_len {
    static constexpr bool val = sizeof...(U) == N;
};

// NOLINTEND(readability-identifier-naming)

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_TRAITS_HPP_
