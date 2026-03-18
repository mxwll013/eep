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

#ifndef SRR_IMPL_SPAN_HPP_
#define SRR_IMPL_SPAN_HPP_

#include "srr/mem.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T> class Span {
public:
    // NOLINTNEXTLINE(readability-identifier-naming)
    using val_t = T;

    constexpr Span() noexcept;
    constexpr Span(T *p) noexcept;
    constexpr Span(T *p, usize n) noexcept;
    template<usize N> constexpr Span(T (&arr)[N + 1]) noexcept;

    constexpr                       operator Span<const T>() const noexcept;

    [[nodiscard]] constexpr usize   len() const noexcept;
    [[nodiscard]] constexpr bool    empty() const noexcept;

    [[nodiscard]] constexpr T      &operator[](usize i) const noexcept;
    [[nodiscard]] constexpr T      &first() const noexcept;
    [[nodiscard]] constexpr T      &last() const noexcept;

    [[nodiscard]] constexpr T      *data() const noexcept;
    [[nodiscard]] constexpr T      *begin() const noexcept;
    [[nodiscard]] constexpr T      *end() const noexcept;

    [[nodiscard]] constexpr usize   copy(Span<const T> src) const noexcept;

    [[nodiscard]] constexpr Span<T> head(usize n) const noexcept;
    [[nodiscard]] constexpr Span<T> tail(usize n) const noexcept;
    [[nodiscard]] constexpr Span<T> span(usize s) const noexcept;
    [[nodiscard]] constexpr Span<T> span(usize s, usize e) const noexcept;

private:
    T    *p_;
    usize len_;
};

// === impl ===

template<typename T>
constexpr Span<T>::Span() noexcept : p_{ nullptr }, len_{ 0 } {}

template<typename T>
constexpr Span<T>::Span(T *p) noexcept : p_{ p }, len_{ 0 } {
    while (p_[len_]) ++len_;
}

template<typename T>
constexpr Span<T>::Span(T *p, usize n) noexcept : p_{ p }, len_{ n } {}

template<typename T>
template<usize N>
constexpr Span<T>::Span(T (&arr)[N + 1]) noexcept : p_{ arr }, len_{ N } {}

template<typename T>
constexpr Span<T>::operator Span<const T>() const noexcept {
    return { p_, len_ };
}

template<typename T> constexpr usize Span<T>::len() const noexcept {
    return len_;
}

template<typename T> constexpr bool Span<T>::empty() const noexcept {
    return len_ == 0;
}

template<typename T> constexpr T &Span<T>::operator[](usize i) const noexcept {
    return p_[i];
}

template<typename T> constexpr T &Span<T>::first() const noexcept {
    return p_[0];
}

template<typename T> constexpr T &Span<T>::last() const noexcept {
    return p_[len_ - 1];
}

template<typename T> constexpr T *Span<T>::data() const noexcept { return p_; }

template<typename T> constexpr T *Span<T>::begin() const noexcept { return p_; }

template<typename T> constexpr T *Span<T>::end() const noexcept {
    return p_ + len_;
}

template<typename T>
constexpr usize Span<T>::copy(Span<const T> src) const noexcept {
    return mem::copye(p_, src.data(), len_, src.len());
}

template<typename T> constexpr Span<T> Span<T>::head(usize n) const noexcept {
    return { p_, n };
}

template<typename T> constexpr Span<T> Span<T>::tail(usize n) const noexcept {
    return { p_ + (len_ - n), n };
}

template<typename T> constexpr Span<T> Span<T>::span(usize s) const noexcept {
    return { p_ + s, len_ - s };
}

template<typename T>
constexpr Span<T> Span<T>::span(usize s, usize e) const noexcept {
    return { p_ + s, e - s };
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_SPAN_HPP_
