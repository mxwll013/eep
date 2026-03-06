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

#include "srr/impl/Arr.hpp"
#include "srr/impl/Span.hpp"
#include "srr/impl/Str.hpp"
#include "srr/impl/ansi.hpp"

#include "srr/types.hpp"

#define SRR_BLACK(...)   SRR_IMPL_ANSI_BLACK(__VA_ARGS__)
#define SRR_RED(...)     SRR_IMPL_ANSI_RED(__VA_ARGS__)
#define SRR_GREEN(...)   SRR_IMPL_ANSI_GREEN(__VA_ARGS__)
#define SRR_YELLOW(...)  SRR_IMPL_ANSI_YELLOW(__VA_ARGS__)
#define SRR_BLUE(...)    SRR_IMPL_ANSI_BLUE(__VA_ARGS__)
#define SRR_MAGENTA(...) SRR_IMPL_ANSI_MAGENTA(__VA_ARGS__)
#define SRR_CYAN(...)    SRR_IMPL_ANSI_CYAN(__VA_ARGS__)
#define SRR_WHITE(...)   SRR_IMPL_ANSI_WHITE(__VA_ARGS__)

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// String (owning)
using str                      = impl::Str<char>;

// String view (mutable)
using strb                     = impl::Span<char>;

// String view (immutable)
using strv                     = impl::Span<const char>;

// Fixed string
template<usize N> using fx_str = impl::Arr<char, N>;

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_STR_HPP_
