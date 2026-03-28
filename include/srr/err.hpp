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

#ifndef SRR_ERR_HPP_
#define SRR_ERR_HPP_

#include "srr/impl/Err.hpp"
#include "srr/impl/Res.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// Termination code
using terc                     = impl::Ter::Code;

// Termination
using ter                      = impl::Ter;

// Error code
using errc                     = impl::Err::Code;

// Error
using err                      = impl::Err;

// Result
template<typename T> using res = impl::Res<T, err>;

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_ERR_HPP_
