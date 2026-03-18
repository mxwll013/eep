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

template<typename T, usz N> class Arr {
public:
    // NOLINTNEXTLINE(readability-identifier-naming)
    using val_t = T;

    consteval Arr() noexcept;
    consteval Arr(const T (&arr)[N + 1]) noexcept;
    template<typename... U> constexpr Arr(U &&...args) noexcept;

    constexpr                        operator Span<T>() noexcept;
    constexpr                        operator Span<const T>() const noexcept;

    [[nodiscard]] constexpr usz      len() const noexcept;
    [[nodiscard]] constexpr bool     empty() const noexcept;

    [[nodiscard]] constexpr const T &operator[](usz i) const noexcept;
    [[nodiscard]] constexpr T       &operator[](usz i) noexcept;
    [[nodiscard]] constexpr const T &first() const noexcept;
    [[nodiscard]] constexpr T       &first() noexcept;
    [[nodiscard]] constexpr const T &last() const noexcept;
    [[nodiscard]] constexpr T       &last() noexcept;

    [[nodiscard]] constexpr const T *data() const noexcept;
    [[nodiscard]] constexpr T       *data() noexcept;
    [[nodiscard]] constexpr const T *begin() const noexcept;
    [[nodiscard]] constexpr T       *begin() noexcept;
    [[nodiscard]] constexpr const T *end() const noexcept;
    [[nodiscard]] constexpr T       *end() noexcept;

    constexpr usz                    copy(Span<const T> src) noexcept;

    [[nodiscard]] constexpr Span<const T> head(usz n) const noexcept;
    [[nodiscard]] constexpr Span<T>       head(usz n) noexcept;
    [[nodiscard]] constexpr Span<const T> tail(usz n) const noexcept;
    [[nodiscard]] constexpr Span<T>       tail(usz n) noexcept;
    [[nodiscard]] constexpr Span<const T> span(usz s, usz e) const noexcept;
    [[nodiscard]] constexpr Span<T>       span(usz s, usz e) noexcept;
    [[nodiscard]] constexpr Span<const T> span(usz s) const noexcept;
    [[nodiscard]] constexpr Span<T>       span(usz s) noexcept;
    [[nodiscard]] constexpr Span<const T> span() const noexcept;
    [[nodiscard]] constexpr Span<T>       span() noexcept;

private:
    T arr_[N > 0 ? N : 1] = {};
};

// === impl ===

template<typename T, usz N> consteval Arr<T, N>::Arr() noexcept {
    for (usz i = 0; i < N; ++i) arr_[i] = {};
}

template<typename T, usz N>
consteval Arr<T, N>::Arr(const T (&arr)[N + 1]) noexcept {
    for (usz i = 0; i < N; ++i) arr_[i] = arr[i];
}

template<typename T, usz N>
template<typename... U>
constexpr Arr<T, N>::Arr(U &&...args) noexcept :
    arr_{ static_cast<T>(fwd<U>(args))... } {
    static_assert(is_len_v<N, U...>);
}

template<typename T, usz N> constexpr Arr<T, N>::operator Span<T>() noexcept {
    return { arr_, N };
}

template<typename T, usz N>
constexpr Arr<T, N>::operator Span<const T>() const noexcept {
    return { arr_, N };
}

template<typename T, usz N> constexpr usz Arr<T, N>::len() const noexcept {
    return N;
}

template<typename T, usz N> constexpr bool Arr<T, N>::empty() const noexcept {
    return N == 0;
}

template<typename T, usz N> constexpr T &Arr<T, N>::operator[](usz i) noexcept {
    return arr_[i];
}

template<typename T, usz N>
constexpr const T &Arr<T, N>::operator[](usz i) const noexcept {
    return arr_[i];
}

template<typename T, usz N> constexpr T &Arr<T, N>::first() noexcept {
    return arr_[0];
}

template<typename T, usz N>
constexpr const T &Arr<T, N>::first() const noexcept {
    return arr_[0];
}

template<typename T, usz N> constexpr T &Arr<T, N>::last() noexcept {
    return arr_[N - 1];
}

template<typename T, usz N>
constexpr const T &Arr<T, N>::last() const noexcept {
    return arr_[N - 1];
}

template<typename T, usz N> constexpr T *Arr<T, N>::data() noexcept {
    return arr_;
}

template<typename T, usz N>
constexpr const T *Arr<T, N>::data() const noexcept {
    return arr_;
}

template<typename T, usz N> constexpr T *Arr<T, N>::begin() noexcept {
    return arr_;
}

template<typename T, usz N>
constexpr const T *Arr<T, N>::begin() const noexcept {
    return arr_;
}

template<typename T, usz N> constexpr T *Arr<T, N>::end() noexcept {
    return arr_ + N;
}

template<typename T, usz N> constexpr const T *Arr<T, N>::end() const noexcept {
    return arr_ + N;
}

template<typename T, usz N>
constexpr usz Arr<T, N>::copy(Span<const T> src) noexcept {
    return mem::copye(arr_, src.data(), N, src.len());
}

template<typename T, usz N>
constexpr Span<const T> Arr<T, N>::head(usz n) const noexcept {
    return { arr_, n };
}

template<typename T, usz N> constexpr Span<T> Arr<T, N>::head(usz n) noexcept {
    return { arr_, n };
}

template<typename T, usz N>
constexpr Span<const T> Arr<T, N>::tail(usz n) const noexcept {
    return { arr_ + (N - n), n };
}

template<typename T, usz N> constexpr Span<T> Arr<T, N>::tail(usz n) noexcept {
    return { arr_ + (N - n), n };
}

template<typename T, usz N>
constexpr Span<const T> Arr<T, N>::span(usz s, usz e) const noexcept {
    return { arr_ + s, e - s };
}

template<typename T, usz N>
constexpr Span<T> Arr<T, N>::span(usz s, usz e) noexcept {
    return { arr_ + s, e - s };
}

template<typename T, usz N>
constexpr Span<const T> Arr<T, N>::span(usz s) const noexcept {
    return { arr_ + s, N - s };
}

template<typename T, usz N> constexpr Span<T> Arr<T, N>::span(usz s) noexcept {
    return { arr_ + s, N - s };
}

template<typename T, usz N>
constexpr Span<const T> Arr<T, N>::span() const noexcept {
    return *this;
}

template<typename T, usz N> constexpr Span<T> Arr<T, N>::span() noexcept {
    return *this;
}

} // namespace impl
} // namespace srr
#endif // SRR_IMPL_ARR_HPP_
