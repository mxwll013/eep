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

#include "srr/impl/Fmter.hpp"

#include "srr/err.hpp"
#include "srr/str.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTNEXTLINE(readability-identifier-naming)
using fmter = impl::Fmter<byte>;
// NOLINTEND(readability-identifier-naming)

constexpr void                 fmt(fmter &buf, nil v) noexcept;
constexpr void                 fmt(fmter &buf, bool v) noexcept;
constexpr void                 fmt(fmter &buf, byte v) noexcept;

// constexpr void fmt(fmter &buf, f32 v) noexcept;
// constexpr void fmt(fmter &buf, f64 v) noexcept;

constexpr void                 fmt(fmter &buf, ter v) noexcept;
constexpr void                 fmt(fmter &buf, err v) noexcept;

template<usz N> constexpr void fmt(fmter &buf, const byte (&v)[N]) noexcept;
constexpr void                 fmt(fmter &buf, strv v) noexcept;
// constexpr void fmt(fmter &buf, strb v) noexcept;
// constexpr void fmt(fmter &buf, const str &v) noexcept;

template<typename T>
    requires is_int_v<T>
constexpr void fmt(fmter &buf, T v) noexcept;

} // namespace srr

#include "srr/impl/Fmt.hpp"

inline namespace srr {

template<typename T>
concept Fmtable                        = impl::Fmtable<byte, T>;

// NOLINTBEGIN(readability-identifier-naming)

// Format string
template<typename... U> using fmt_str  = impl::Fmt<byte, U...>;

// NOLINTEND(readability-identifier-naming)

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

constexpr void               fmt(fmter &buf, [[maybe_unused]] nil v) noexcept {
    buf.push("(null)");
}

constexpr void fmt(fmter &buf, bool v) noexcept {
    buf.push(v ? "true" : "false");
}

constexpr void fmt(fmter &buf, byte v) noexcept { buf.push(v); }

// constexpr void fmt(fmter &buf, f32 v) noexcept;
// constexpr void fmt(fmter &buf, f64 v) noexcept;

constexpr void fmt(fmter &buf, ter v) noexcept { buf.push(v.msg()); }

constexpr void fmt(fmter &buf, err v) noexcept {
    buf.push(v.msg());

    const strv tr = v.trace();

    if (!tr.empty()) {
        buf.push(" '");
        buf.push(tr);
        buf.push("'");
    }
}

template<usz N> constexpr void fmt(fmter &buf, const byte (&v)[N]) noexcept {
    buf.push(v);
}

constexpr void fmt(fmter &buf, strv v) noexcept { buf.push(v); }

template<typename T>
    requires is_int_v<T>
constexpr void fmt(fmter &buf, T v) noexcept {
    using U = mk_u_t<T>;
    U u;

    if constexpr (is_s_v<T>) {
        if (v < 0) {
            buf.push('-');
            u = 0 - static_cast<U>(v);
        } else {
            u = static_cast<U>(v);
        }

    } else {
        u = v;
    }

    fx_str<32> rev;

    // NOLINTNEXTLINE(misc-const-correctness)
    byte      *p = rev.end();

    while (u >= 100) {
        usz idx  = (u % 100) * 2;
        u       /= 100;

        *--p     = DIGIT_LUT[idx + 1];
        *--p     = DIGIT_LUT[idx];
    }

    if (u < 10) {
        *--p = static_cast<byte>(u + '0');
    } else {
        usz idx = u * 2;
        *--p    = DIGIT_LUT[idx + 1];
        *--p    = DIGIT_LUT[idx];
    }

    buf.push({ p, static_cast<usz>(rev.end() - p) });
}

} // namespace srr

#endif // SRR_FMT_HPP_
