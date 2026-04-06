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

#ifndef SRR_HASH_HPP_
#define SRR_HASH_HPP_

#include "srr/impl/Hasher.hpp"

#include "srr/mem.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// 64 bit hasher
using hasher64 = impl::Hasher<u64>;

// 32 bit hasher
using hasher32 = impl::Hasher<u32>;

// Default hasher (64 bit)
using hasher   = hasher64;

// NOLINTEND(readability-identifier-naming)

constexpr void                 hash(hasher &h, f32 v) noexcept;
constexpr void                 hash(hasher &h, f64 v) noexcept;

template<usz N> constexpr void hash(hasher &h, const byte (&v)[N + 1]) noexcept;
constexpr void                 hash(hasher &h, const strv &v) noexcept;

template<typename T>
    requires is_int_v<T>
constexpr void hash(hasher &h, T v) noexcept;

} // namespace srr

#include "srr/impl/HashMap.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// 32 bit hash map
template<typename K, typename V, mem::Alloc A = mem::base_alloc<byte>>
using hmap32 = impl::HashMap<u32, K, V, A>;

// 64 bit hash map
template<typename K, typename V, mem::Alloc A = mem::base_alloc<byte>>
using hmap64 = impl::HashMap<u64, K, V, A>;

// Default hash map (64 bit)
template<typename K, typename V, mem::Alloc A = mem::base_alloc<byte>>
using hmap = hmap64<K, V, A>;

// NOLINTEND(readability-identifier-naming)

template<typename T>
concept Hashable64 = impl::Hashable<u64, T>;

template<typename T>
concept Hashable32 = impl::Hashable<u32, T>;

template<typename T>
concept Hashable = Hashable64<T>;

// === impl ===

constexpr void hash(hasher &h, f32 v) noexcept { h.push(v); }

constexpr void hash(hasher &h, f64 v) noexcept { h.push(v); }

template<usz N>
constexpr void hash(hasher &h, const byte (&v)[N + 1]) noexcept {
    h.push(v, N);
}

constexpr void hash(hasher &h, const strv &v) noexcept {
    h.push(v.data(), v.len());
}

template<typename T>
    requires is_int_v<T>
constexpr void hash(hasher &h, T v) noexcept {
    h.push(v);
}

} // namespace srr

#endif // SRR_HASH_HPP_
