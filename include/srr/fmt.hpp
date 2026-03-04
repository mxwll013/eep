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

#ifndef SRR_FMT_HPP_
#define SRR_FMT_HPP_

#include "srr/impl/Fmt.hpp"

#include "srr/err.hpp"
#include "srr/str.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

template<typename T>
concept CharFormattable                = impl::Formattable<char, T>;

// Format string
template<typename... U> using fmt_str  = impl::Fmt<char, U...>;

// === impl ===

static constexpr fx_str<200> DIGIT_LUT = "00010203040506070809"
                                         "10111213141516171819"
                                         "20212223242526272829"
                                         "30212223242526272829"
                                         "40414243444546474849"
                                         "50515253545556575859"
                                         "60616263646566676869"
                                         "70717273747576777879"
                                         "80818283848586878889"
                                         "90919293949596979899";

constexpr usize fmt(const strb &buf, [[maybe_unused]] nil v) noexcept {
    return buf.copy("nullptr");
}

constexpr usize fmt(const strb &buf, bool v) noexcept {
    const strv s = v ? "true" : "false";
    return buf.copy(s);
}

constexpr usize fmt(const strb &buf, char v) noexcept {
    buf[0] = v;
    return 1;
}

// constexpr usize fmt(const strb &buf, f32 v) noexcept;
// constexpr usize fmt(const strb &buf, f64 v) noexcept;

constexpr usize fmt(const strb &buf, exitc v) noexcept {
    return buf.copy(msg(v));
}

constexpr usize fmt(const strb &buf, errc v) noexcept {
    return buf.copy(msg(v));
}

constexpr usize fmt(const strb &buf, err v) noexcept {
    return buf.copy(v.msg());
}

template<usize N>
constexpr usize fmt(const strb &buf, const char (&v)[N]) noexcept {
    return buf.copy(v);
}

constexpr usize fmt(const strb &buf, strv v) noexcept { return buf.copy(v); }

template<Int I> constexpr usize fmt(const strb &buf, I v) noexcept {
    using U = make_unsigned_t<I>;
    U     u;
    usize i = 0;

    if constexpr (is_signed_v<I>) {
        if (v < 0) {
            buf[i++] = '-';
            u        = 0 - static_cast<U>(v);
        } else {
            u = static_cast<U>(v);
        }

    } else {
        u = v;
    }

    fx_str<32> rev;
    char      *p = rev.end();

    while (u >= 100) {
        usize idx  = (u % 100) * 2;
        u         /= 100;

        *--p       = DIGIT_LUT[idx + 1];
        *--p       = DIGIT_LUT[idx];
    }

    if (u < 10) {
        *--p = static_cast<char>(u + '0');
    } else {
        usize idx = u * 2;
        *--p      = DIGIT_LUT[idx + 1];
        *--p      = DIGIT_LUT[idx];
    }

    for (; p < rev.end(); ++p) buf[i++] = *p;

    return i;
}

// NOLINTEND(readability-identifier-naming)

} // namespace srr

#endif // SRR_FMT_HPP_
