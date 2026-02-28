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

#ifndef SRR_IMPL_STR_HPP_
#define SRR_IMPL_STR_HPP_

#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T>
class Str {
public:
    [[nodiscard]] constexpr Str() noexcept;
    [[nodiscard]] constexpr Str(T *p, usize n) noexcept;

    [[nodiscard]] constexpr T    *data() const noexcept;
    [[nodiscard]] constexpr usize len() const noexcept;

private:
    T    *p_;
    usize len_;
};

// === impl ===

template<typename T>
constexpr Str<T>::Str() noexcept : p_{ nullptr }, len_{ 0 } {}

template<typename T>
constexpr Str<T>::Str(T *p, usize n) noexcept : p_{ p }, len_{ n } {}

template<typename T>
constexpr T *Str<T>::data() const noexcept {
    return p_;
}

template<typename T>
constexpr usize Str<T>::len() const noexcept {
    return len_;
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_STR_HPP_
