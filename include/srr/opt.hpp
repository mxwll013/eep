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

#ifndef SRR_OPT_HPP_
#define SRR_OPT_HPP_

#include "srr/impl/Res.hpp"

#include "srr/err.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// Optional (nullable value)
// template<typename T>
// using opt = impl::Opt<T>;

// Result (value or error)
template<typename T> using res = impl::Res<T, err>;

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_OPT_HPP_
