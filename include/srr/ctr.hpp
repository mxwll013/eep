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

#ifndef SRR_CTR_HPP_
#define SRR_CTR_HPP_

#include "srr/impl/Arr.hpp"
#include "srr/impl/List.hpp"
#include "srr/impl/Span.hpp"

#include "srr/mem.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// Dynamic array (owning)
template<typename T, mem::Alloc A = mem::base_alloc<T>>
using list                              = impl::List<T, A>;

// Array (fixed-size, owning)
template<typename T, usize N> using arr = impl::Arr<T, N>;

// Span (non-owning view)
template<typename T> using span         = impl::Span<T>;

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_CTR_HPP_
