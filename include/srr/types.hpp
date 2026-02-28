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

#ifndef SRR_TYPES_HPP_
#define SRR_TYPES_HPP_

#include <cstddef>
#include <cstdint>

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

using i8                  = std::int8_t;
using i16                 = std::int16_t;
using i32                 = std::int32_t;
using i64                 = std::int64_t;
using isize               = std::ptrdiff_t;

using u8                  = std::uint8_t;
using u16                 = std::uint16_t;
using u32                 = std::uint32_t;
using u64                 = std::uint64_t;
using usize               = std::size_t;

using f32                 = float;
using f64                 = double;

// NOLINTEND(readability-identifier-naming)

constexpr i8    MIN_I8    = INT8_MIN;
constexpr i16   MIN_I16   = INT16_MIN;
constexpr i32   MIN_I32   = INT32_MIN;
constexpr i64   MIN_I64   = INT64_MIN;
constexpr isize MIN_ISIZE = PTRDIFF_MIN;

constexpr i8    MAX_I8    = INT8_MIN;
constexpr i16   MAX_I16   = INT16_MIN;
constexpr i32   MAX_I32   = INT32_MIN;
constexpr i64   MAX_I64   = INT64_MIN;
constexpr isize MAX_ISIZE = PTRDIFF_MAX;

constexpr u8    MAX_U8    = UINT8_MAX;
constexpr u16   MAX_U16   = UINT16_MAX;
constexpr u32   MAX_U32   = UINT32_MAX;
constexpr u64   MAX_U64   = UINT64_MAX;
constexpr usize MAX_USIZE = SIZE_MAX;

constexpr f32   MAX_F32   = __FLT_MAX__;
constexpr f64   MAX_F64   = __DBL_MAX__;

constexpr f32   MIN_F32   = __FLT_MIN__;
constexpr f64   MIN_F64   = __DBL_MIN__;

} // namespace srr

#endif // SRR_TYPES_HPP_
