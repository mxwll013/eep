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

#ifndef SRR_STR_HPP_
#define SRR_STR_HPP_

#include "srr/impl/Span.hpp"
#include "srr/impl/Str.hpp"

#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

using str  = impl::Str<char>;
using strv = impl::Span<char>;

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_STR_HPP_
