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

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

using nil    = decltype(nullptr);

using byte   = char;
using sbyte  = signed char;
using ubyte  = unsigned char;
using sshort = signed short;
using ushort = unsigned short;
using sint   = signed int;
using uint   = unsigned int;
using slong  = signed long;
using ulong  = unsigned long;
using sll    = signed long long;
using ull    = unsigned long long;

using i8     = __INT8_TYPE__;
using i16    = __INT16_TYPE__;
using i32    = __INT32_TYPE__;
using i64    = __INT64_TYPE__;
using isz    = __PTRDIFF_TYPE__;
using iptr   = __INTPTR_TYPE__;

using u8     = __UINT8_TYPE__;
using u16    = __UINT16_TYPE__;
using u32    = __UINT32_TYPE__;
using u64    = __UINT64_TYPE__;
using usz    = __SIZE_TYPE__;
using uptr   = __UINTPTR_TYPE__;

using f32    = float;
using f64    = double;

template<typename T, T C> struct type_k;
template<bool C> using bool_k = type_k<bool, C>;

template<typename T> struct umax;
template<typename T> struct smin;
template<typename T> struct smax;
template<typename T> struct is_s;
template<typename T> struct is_u;
template<typename T> struct min;
template<typename T> struct max;

template<typename T> constexpr T    umax_v = umax<T>::val;
template<typename T> constexpr T    smin_v = smin<T>::val;
template<typename T> constexpr T    smax_v = smax<T>::val;
template<typename T> constexpr bool is_s_v = is_s<T>::val;
template<typename T> constexpr bool is_u_v = is_u<T>::val;
template<typename T> constexpr T    min_v  = min<T>::val;
template<typename T> constexpr T    max_v  = max<T>::val;

template<typename T, T C> struct type_k {
    static constexpr T val = C;
};

template<typename T> struct umax : type_k<T, static_cast<T>(-1)> {};

template<typename T>
// NOLINTNEXTLINE(hicpp-signed-bitwise)
struct smin : type_k<T, static_cast<T>(T{ 1 } << (sizeof(T) * 8 - 1))> {};

template<typename T>
// NOLINTNEXTLINE(hicpp-signed-bitwise)
struct smax : type_k<T, static_cast<T>(~(T{ 1 } << (sizeof(T) * 8 - 1)))> {};

template<typename T> struct is_s : bool_k < umax_v<T><0> {};

template<typename T> struct is_u : bool_k<0 < umax_v<T>> {};

template<typename T> struct min : type_k<T, is_s_v<T> ? smin_v<T> : 0> {};

template<typename T>
struct max : type_k<T, is_s_v<T> ? smax_v<T> : umax_v<T>> {};

// NOLINTEND(readability-identifier-naming)

constexpr i8   MIN_I8   = min_v<i8>;
constexpr i16  MIN_I16  = min_v<i16>;
constexpr i32  MIN_I32  = min_v<i32>;
constexpr i64  MIN_I64  = min_v<i64>;
constexpr isz  MIN_ISZ  = min_v<isz>;
constexpr iptr MIN_IPTR = min_v<iptr>;

constexpr i8   MAX_I8   = max_v<i8>;
constexpr i16  MAX_I16  = max_v<i16>;
constexpr i32  MAX_I32  = max_v<i32>;
constexpr i64  MAX_I64  = max_v<i64>;
constexpr isz  MAX_ISZ  = max_v<isz>;
constexpr iptr MAX_IPTR = max_v<iptr>;

constexpr u8   MAX_U8   = max_v<u8>;
constexpr u16  MAX_U16  = max_v<u16>;
constexpr u32  MAX_U32  = max_v<u32>;
constexpr u64  MAX_U64  = max_v<u64>;
constexpr usz  MAX_USZ  = max_v<usz>;
constexpr uptr MAX_UPTR = max_v<uptr>;

constexpr f32  MAX_F32  = __FLT_MAX__;
constexpr f64  MAX_F64  = __DBL_MAX__;

constexpr f32  MIN_F32  = __FLT_MIN__;
constexpr f64  MIN_F64  = __DBL_MIN__;

consteval i8   operator""_i8(ull v) noexcept;
consteval i16  operator""_i16(ull v) noexcept;
consteval i32  operator""_i32(ull v) noexcept;
consteval i64  operator""_i64(ull v) noexcept;
consteval isz  operator""_isz(ull v) noexcept;
consteval iptr operator""_iptr(ull v) noexcept;
consteval u8   operator""_u8(ull v) noexcept;
consteval u16  operator""_u16(ull v) noexcept;
consteval u32  operator""_u32(ull v) noexcept;
consteval u64  operator""_u64(ull v) noexcept;
consteval usz  operator""_usz(ull v) noexcept;

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

} // namespace srr

#endif // SRR_TYPES_HPP_
