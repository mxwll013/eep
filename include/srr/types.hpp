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

#include "srr/impl/lang.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

using nil                                 = decltype(nullptr);

using byte                                = char;
using sbyte                               = signed char;
using ubyte                               = unsigned char;
using sshort                              = signed short;
using ushort                              = unsigned short;
using sint                                = signed int;
using uint                                = unsigned int;
using slong                               = signed long;
using ulong                               = unsigned long;
using sll                                 = signed long long;
using ull                                 = unsigned long long;

using i8                                  = __INT8_TYPE__;
using i16                                 = __INT16_TYPE__;
using i32                                 = __INT32_TYPE__;
using i64                                 = __INT64_TYPE__;
using isz                                 = __PTRDIFF_TYPE__;
using iptr                                = __INTPTR_TYPE__;

using u8                                  = __UINT8_TYPE__;
using u16                                 = __UINT16_TYPE__;
using u32                                 = __UINT32_TYPE__;
using u64                                 = __UINT64_TYPE__;
using usz                                 = __SIZE_TYPE__;
using uptr                                = __UINTPTR_TYPE__;

using f32                                 = float;
using f64                                 = double;

template<typename T> constexpr T min_v    = impl::min_v<T>;
template<typename T> constexpr T max_v    = impl::max_v<T>;

// NOLINTEND(readability-identifier-naming)

constexpr i8                     MIN_I8   = min_v<i8>;
constexpr i16                    MIN_I16  = min_v<i16>;
constexpr i32                    MIN_I32  = min_v<i32>;
constexpr i64                    MIN_I64  = min_v<i64>;
constexpr isz                    MIN_ISZ  = min_v<isz>;
constexpr iptr                   MIN_IPTR = min_v<iptr>;

constexpr i8                     MAX_I8   = max_v<i8>;
constexpr i16                    MAX_I16  = max_v<i16>;
constexpr i32                    MAX_I32  = max_v<i32>;
constexpr i64                    MAX_I64  = max_v<i64>;
constexpr isz                    MAX_ISZ  = max_v<isz>;
constexpr iptr                   MAX_IPTR = max_v<iptr>;

constexpr u8                     MAX_U8   = max_v<u8>;
constexpr u16                    MAX_U16  = max_v<u16>;
constexpr u32                    MAX_U32  = max_v<u32>;
constexpr u64                    MAX_U64  = max_v<u64>;
constexpr usz                    MAX_USZ  = max_v<usz>;
constexpr uptr                   MAX_UPTR = max_v<uptr>;

constexpr f32                    MAX_F32  = __FLT_MAX__;
constexpr f64                    MAX_F64  = __DBL_MAX__;

constexpr f32                    MIN_F32  = __FLT_MIN__;
constexpr f64                    MIN_F64  = __DBL_MIN__;

consteval i8                     operator""_i8(ull v) noexcept;
consteval i16                    operator""_i16(ull v) noexcept;
consteval i32                    operator""_i32(ull v) noexcept;
consteval i64                    operator""_i64(ull v) noexcept;
consteval isz                    operator""_isz(ull v) noexcept;
consteval iptr                   operator""_iptr(ull v) noexcept;
consteval u8                     operator""_u8(ull v) noexcept;
consteval u16                    operator""_u16(ull v) noexcept;
consteval u32                    operator""_u32(ull v) noexcept;
consteval u64                    operator""_u64(ull v) noexcept;
consteval usz                    operator""_usz(ull v) noexcept;
consteval uptr                   operator""_uptr(ull v) noexcept;

consteval f32                    operator""_f32(long double v) noexcept;
consteval f64                    operator""_f64(long double v) noexcept;

// === impl ===

consteval i8   operator""_i8(ull v) noexcept { return static_cast<i8>(v); }

consteval i16  operator""_i16(ull v) noexcept { return static_cast<i16>(v); }

consteval i32  operator""_i32(ull v) noexcept { return static_cast<i32>(v); }

consteval i64  operator""_i64(ull v) noexcept { return static_cast<i64>(v); }

consteval isz  operator""_isz(ull v) noexcept { return static_cast<isz>(v); }

consteval iptr operator""_iptr(ull v) noexcept { return static_cast<iptr>(v); }

consteval u8   operator""_u8(ull v) noexcept { return static_cast<u8>(v); }

consteval u16  operator""_u16(ull v) noexcept { return static_cast<u16>(v); }

consteval u32  operator""_u32(ull v) noexcept { return static_cast<u32>(v); }

consteval u64  operator""_u64(ull v) noexcept { return static_cast<u64>(v); }

consteval usz  operator""_usz(ull v) noexcept { return static_cast<usz>(v); }

consteval uptr operator""_uptr(ull v) noexcept { return static_cast<uptr>(v); }

consteval f32  operator""_f32(long double v) noexcept {
    return static_cast<f32>(v);
}

consteval f64 operator""_f64(long double v) noexcept {
    return static_cast<f64>(v);
}

} // namespace srr

#endif // SRR_TYPES_HPP_
