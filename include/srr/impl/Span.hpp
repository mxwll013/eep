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

#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T>
class Span {
public:
    [[nodiscard]] constexpr Span() noexcept;
    [[nodiscard]] constexpr Span(const T *p, usize n) noexcept;
    [[nodiscard]] constexpr Span(const T *s, const T *e) noexcept;
    template<usize N>
    [[nodiscard]] constexpr Span(const T (&p)[N]) noexcept;

    [[nodiscard]] constexpr const T *data() const noexcept;
    [[nodiscard]] constexpr usize    len() const noexcept;

private:
    const T *p_;
    usize    len_;
};

// === impl ===

template<typename T>
constexpr Span<T>::Span() noexcept : p_{ nullptr }, len_{ 0 } {}

template<typename T>
constexpr Span<T>::Span(const T *p, usize n) noexcept : p_{ p }, len_{ n } {}

template<typename T>
template<usize N>
constexpr Span<T>::Span(const T (&p)[N]) noexcept : p_{ p }, len_{ N } {}

template<typename T>
constexpr Span<T>::Span(const T *s, const T *e) noexcept :
    p_{ s },
    len_{ static_cast<usize>(e - s) } {}

template<typename T>
constexpr const T *Span<T>::data() const noexcept {
    return p_;
}

template<typename T>
constexpr usize Span<T>::len() const noexcept {
    return len_;
}

} // namespace impl
} // namespace srr
#endif // SRR_IMPL_SPAN_HPP_
