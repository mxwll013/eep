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

#ifndef SRR_IMPL_ARR_HPP_
#define SRR_IMPL_ARR_HPP_

#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T, usize N>
class Arr {
public:
    [[nodiscard]] constexpr Arr(const T (&arr)[N]) noexcept;
    template<typename... U>
    [[nodiscard]] constexpr Arr(U &&...args) noexcept;

    [[nodiscard]] constexpr T       &operator[](usize i) noexcept;
    [[nodiscard]] constexpr const T &operator[](usize i) const noexcept;

    [[nodiscard]] constexpr usize    len() const noexcept;

private:
    T arr_[N] = {};
};

// === impl ===

template<typename T, usize N>
constexpr Arr<T, N>::Arr(const T (&arr)[N]) noexcept {
    for (usize i = 0; i < N; ++i) arr_[i] = arr[i];
}

template<typename T, usize N>
template<typename... U>
constexpr Arr<T, N>::Arr(U &&...args) noexcept :
    arr_{ static_cast<T>(fwd<U>(args))... } {
    static_assert(is_len_v<N, U...>, "Number of arguments must be equal to N");
}

template<typename T, usize N>
constexpr T &Arr<T, N>::operator[](usize i) noexcept {
    return arr_[i];
}

template<typename T, usize N>
constexpr const T &Arr<T, N>::operator[](usize i) const noexcept {
    return arr_[i];
}

template<typename T, usize N>
constexpr usize Arr<T, N>::len() const noexcept {
    return N;
}

} // namespace impl
} // namespace srr
#endif // SRR_IMPL_ARR_HPP_
