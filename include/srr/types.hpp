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

using nil                 = decltype(nullptr);

using i8                  = int8_t;
using i16                 = int16_t;
using i32                 = int32_t;
using i64                 = int64_t;
using isize               = ptrdiff_t;

using u8                  = uint8_t;
using u16                 = uint16_t;
using u32                 = uint32_t;
using u64                 = uint64_t;
using usize               = size_t;

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

consteval i8    operator""_i8(unsigned long long v) noexcept {
    return static_cast<i8>(v);
}

consteval i16 operator""_i16(unsigned long long v) noexcept {
    return static_cast<i16>(v);
}

consteval i32 operator""_i32(unsigned long long v) noexcept {
    return static_cast<i32>(v);
}

consteval i64 operator""_i64(unsigned long long v) noexcept {
    return static_cast<i64>(v);
}

consteval u8 operator""_u8(unsigned long long v) noexcept {
    return static_cast<u8>(v);
}

consteval u16 operator""_u16(unsigned long long v) noexcept {
    return static_cast<u16>(v);
}

consteval u32 operator""_u32(unsigned long long v) noexcept {
    return static_cast<u32>(v);
}

consteval u64 operator""_u64(unsigned long long v) noexcept {
    return static_cast<u64>(v);
}

} // namespace srr

#endif // SRR_TYPES_HPP_
