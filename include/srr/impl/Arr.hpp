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

#include "srr/impl/Span.hpp"

#include "srr/mem.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T, usize N> class Arr {
public:
    consteval Arr() noexcept;
    consteval Arr(const T (&arr)[N + 1]) noexcept;
    template<typename... U> constexpr Arr(U &&...args) noexcept;

    [[nodiscard]] constexpr T            &operator[](usize i) noexcept;
    [[nodiscard]] constexpr const T      &operator[](usize i) const noexcept;

    [[nodiscard]] constexpr usize         len() const noexcept;
    [[nodiscard]] constexpr T            *data() noexcept;
    [[nodiscard]] constexpr const T      *data() const noexcept;
    [[nodiscard]] constexpr T            *end() noexcept;
    [[nodiscard]] constexpr const T      *end() const noexcept;

    [[nodiscard]] constexpr usize         copy(Span<const T> src) noexcept;

    [[nodiscard]] constexpr Span<T>       span() noexcept;
    [[nodiscard]] constexpr Span<const T> span() const noexcept;
    [[nodiscard]] constexpr Span<T>       span(usize s) noexcept;
    [[nodiscard]] constexpr Span<const T> span(usize s) const noexcept;
    [[nodiscard]] constexpr Span<T>       span(usize s, usize e) noexcept;
    [[nodiscard]] constexpr Span<const T> span(usize s, usize e) const noexcept;

    constexpr                             operator Span<T>() noexcept;
    constexpr operator Span<const T>() const noexcept;

private:
    T arr_[N] = {};
};

// === impl ===
template<typename T, usize N> consteval Arr<T, N>::Arr() noexcept {
    for (usize i = 0; i < N; ++i) arr_[i] = {};
}

template<typename T, usize N>
consteval Arr<T, N>::Arr(const T (&arr)[N + 1]) noexcept {
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

template<typename T, usize N> constexpr usize Arr<T, N>::len() const noexcept {
    return N;
}

template<typename T, usize N> constexpr T *Arr<T, N>::data() noexcept {
    return arr_;
}

template<typename T, usize N>
constexpr const T *Arr<T, N>::data() const noexcept {
    return arr_;
}

template<typename T, usize N> constexpr T *Arr<T, N>::end() noexcept {
    return arr_ + N;
}

template<typename T, usize N>
constexpr const T *Arr<T, N>::end() const noexcept {
    return arr_ + N;
}

template<typename T, usize N>
constexpr usize Arr<T, N>::copy(Span<const T> src) noexcept {
    return mem::copye(arr_, src.data(), N, src.len());
}

template<typename T, usize N>
constexpr Span<T> Arr<T, N>::span(usize s, usize e) noexcept {
    return { &arr_[s], e - s };
}

template<typename T, usize N>
constexpr Span<const T> Arr<T, N>::span(usize s, usize e) const noexcept {
    return { &arr_[s], e - s };
}

template<typename T, usize N> constexpr Arr<T, N>::operator Span<T>() noexcept {
    return { arr_, N };
}

template<typename T, usize N>
constexpr Arr<T, N>::operator Span<const T>() const noexcept {
    return { arr_, N };
}

} // namespace impl
} // namespace srr
#endif // SRR_IMPL_ARR_HPP_
