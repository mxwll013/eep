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

#ifndef SRR_IMPL_FMT_HPP_
#define SRR_IMPL_FMT_HPP_

#include "srr/impl/Arr.hpp"
#include "srr/impl/Span.hpp"

#include "srr/err.hpp"
#include "srr/str.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {

constexpr usize fmt(const strb &buf, nil v) noexcept;
constexpr usize fmt(const strb &buf, bool v) noexcept;
constexpr usize fmt(const strb &buf, char v) noexcept;

// constexpr usize fmt(const strb &buf, f32 v) noexcept;
// constexpr usize fmt(const strb &buf, f64 v) noexcept;

constexpr usize fmt(const strb &buf, exitc v) noexcept;
constexpr usize fmt(const strb &buf, errc v) noexcept;
constexpr usize fmt(const strb &buf, err v) noexcept;

template<usize N>
constexpr usize fmt(const strb &buf, const char (&v)[N]) noexcept;
constexpr usize fmt(const strb &buf, strv v) noexcept;

template<Int I> constexpr usize fmt(const strb &buf, I v) noexcept;

namespace impl {

template<typename T, typename U>
concept Fmtable = requires(const Span<T> &buf, const U &u) {
    { fmt(buf, u) } noexcept -> Same<usize>;
};

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
class Fmt {
public:
    template<usize M> consteval Fmt(const T (&p)[M]) noexcept;

    [[nodiscard]] constexpr usize apply(Span<T> buf,
                                        const U &...args) const noexcept;

private:
    static constexpr usize  N = sizeof...(U);

    Span<const T>           str_{};
    Arr<usize, (N + 1) * 2> segs_{};

    consteval void          parse();

    constexpr usize         build(Span<T> buf, usize seg) const noexcept;

    template<typename V, typename... W>
    constexpr usize build(Span<T>  buf,
                          usize    seg,
                          const V &arg,
                          const W &...args) const noexcept;
};

// === impl ===

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
template<usize M>
// NOLINTNEXTLINE(bugprone-exception-escape)
consteval Fmt<T, U...>::Fmt(const T (&p)[M]) noexcept : str_{ p, M-1 } {
    parse();
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
constexpr usize Fmt<T, U...>::apply(Span<T> buf,
                                    const U &...args) const noexcept {
    return build(buf, 0, args...);
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
consteval void Fmt<T, U...>::parse() {
    usize n  = 0;
    segs_[0] = 0;

    for (usize i = 0; i < str_.len(); i++) {
        if (str_[i] == '}') throw "Unmatched '}' in format string!";
        if (str_[i] != '{') continue;
        ++i;

        if (i >= str_.len()) throw "Unexpected end of format string after '{'!";

        if (str_[i] == '{') continue;

        if (str_[i] != '}') throw "Expected '}' after '{' in format string!";

        if (n >= N) throw "Too many format specifiers in format string!";

        segs_[(n * 2) + 1] = i - 1; // End of last segment
        ++n;
        segs_[(n * 2)] = i + 1;     // Start of next segment
    }

    if (n != N)
        throw "Number of format specifiers in format string does not match "
              "number of arguments!";

    segs_[(N * 2) + 1] = str_.len();
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
constexpr usize Fmt<T, U...>::build(Span<T> buf, usize seg) const noexcept {
    usize s = segs_[seg * 2];
    usize e = segs_[(seg * 2) + 1];

    return buf.copy(str_.span(s, e));
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
template<typename V, typename... W>
constexpr usize Fmt<T, U...>::build(Span<T>  buf,
                                    usize    seg,
                                    const V &arg,
                                    const W &...args) const noexcept {
    usize n  = build(buf, seg);
    n       += fmt(buf.span(n), arg);
    return n + build(buf.span(n), seg + 1, args...);
}

} // namespace impl

} // namespace srr

#endif // SRR_IMPL_FMT_HPP_
