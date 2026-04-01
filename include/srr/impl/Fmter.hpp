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

#ifndef SRR_IMPL_FMTER_HPP_
#define SRR_IMPL_FMTER_HPP_

#include "srr/impl/Span.hpp"

#include "srr/err.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T> class Fmter {
public:
    constexpr Fmter(Span<T> buf) noexcept;

    constexpr void                             push(T b) noexcept;
    constexpr void                             push(Span<const T> s) noexcept;

    [[nodiscard]] constexpr res<Span<const T>> done() noexcept;

private:
    Span<T> buf_;
    err     err_;
    usz     len_ = 0;
};

// === impl ===

template<typename T>
constexpr Fmter<T>::Fmter(Span<T> buf) noexcept : buf_{ buf } {}

template<typename T> constexpr void Fmter<T>::push(T b) noexcept {
    if (err_) return;

    if (len_ < 1) {
        err_ = err::FMT_OVERFLOW;
        return;
    }

    buf_[++len_] = b;
}

template<typename T> constexpr void Fmter<T>::push(Span<const T> s) noexcept {
    if (err_) return;

    if (len_ + s.len() > buf_.len()) {
        err_ = { s, err::FMT_OVERFLOW };
        return;
    }

    len_ += buf_.span(len_).copy(s);
}

template<typename T>
[[nodiscard]] constexpr res<Span<const T>> Fmter<T>::done() noexcept {
    if (err_) return err_;

    return buf_.head(len_);
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_FMTER_HPP_
