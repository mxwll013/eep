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

#ifndef SRR_IMPL_HASHER_HPP_
#define SRR_IMPL_HASHER_HPP_

#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T> constexpr T FNV_OFFSET      = {};
template<> inline constexpr u32  FNV_OFFSET<u32> = 0x811C'9DC5_u32;
template<> inline constexpr u64  FNV_OFFSET<u64> = 0xCBF2'9CE4'8422'2325_u64;

template<typename T> constexpr T FNV_PRIME       = {};
template<> inline constexpr u32  FNV_PRIME<u32>  = 0x0100'0193_u32;
template<> inline constexpr u64  FNV_PRIME<u64>  = 0x0000'0100'0000'01B3_u64;

template<typename T> class Hasher {
public:
    constexpr Hasher() noexcept = default;

    constexpr void                      push(const void *p, usz len) noexcept;

    template<typename U> constexpr void push(const U &val) noexcept;

    [[nodiscard]] constexpr T           done() const noexcept;

private:
    T hash_ = FNV_OFFSET<T>;
};

// === impl ===

template<typename T>
constexpr void Hasher<T>::push(const void *p, usz len) noexcept {
    const u8 *data = static_cast<const u8 *>(p);

    // FNV-1a
    // https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
    for (usz i = 0; i < len; ++i) {
        hash_ ^= data[i];
        hash_ *= FNV_PRIME<T>;
    }
}

template<typename T>
template<typename U>
constexpr void Hasher<T>::push(const U &val) noexcept {
    push(&val, sizeof(U));
}

template<typename T> constexpr T Hasher<T>::done() const noexcept {
    return hash_;
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_HASHER_HPP_
