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

constexpr usz                 fmt(const strb &buf, nil v) noexcept;
constexpr usz                 fmt(const strb &buf, bool v) noexcept;
constexpr usz                 fmt(const strb &buf, char v) noexcept;

// constexpr usz fmt(const strb &buf, f32 v) noexcept;
// constexpr usz fmt(const strb &buf, f64 v) noexcept;

constexpr usz                 fmt(const strb &buf, ter v) noexcept;
constexpr usz                 fmt(const strb &buf, err v) noexcept;

template<usz N> constexpr usz fmt(const strb &buf, const char (&v)[N]) noexcept;
constexpr usz                 fmt(const strb &buf, strv v) noexcept;
constexpr usz                 fmt(const strb &buf, strb v) noexcept;
constexpr usz                 fmt(const strb &buf, const str &v) noexcept;

template<Int I> constexpr usz fmt(const strb &buf, I v) noexcept;

namespace impl {

template<typename T, typename U>
concept Fmtable = requires(const Span<T> &buf, const U &u) {
    { fmt(buf, u) } noexcept -> Same<usz>;
};

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
class Fmt {
public:
    template<usz M> consteval Fmt(const T (&p)[M]) noexcept;

    [[nodiscard]] constexpr usz apply(Span<T> buf,
                                      const U &...args) const noexcept;

private:
    static constexpr usz  N = sizeof...(U);

    Span<const T>         str_{};
    Arr<usz, (N + 1) * 2> segs_{};

    consteval void        parse();

    constexpr usz         build(Span<T> buf, usz seg) const noexcept;

    template<typename V, typename... W>
    constexpr usz build(Span<T>  buf,
                        usz      seg,
                        const V &arg,
                        const W &...args) const noexcept;
};

// === impl ===

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
template<usz M>
// NOLINTNEXTLINE(bugprone-exception-escape)
consteval Fmt<T, U...>::Fmt(const T (&p)[M]) noexcept : str_{ p, M-1 } {
    parse();
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
constexpr usz Fmt<T, U...>::apply(Span<T> buf,
                                  const U &...args) const noexcept {
    return build(buf, 0, args...);
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
consteval void Fmt<T, U...>::parse() {
    usz n    = 0;
    segs_[0] = 0;

    for (usz i = 0; i < str_.len(); i++) {
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
constexpr usz Fmt<T, U...>::build(Span<T> buf, usz seg) const noexcept {
    usz s = segs_[seg * 2];
    usz e = segs_[(seg * 2) + 1];

    return buf.copy(str_.span(s, e));
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
template<typename V, typename... W>
constexpr usz Fmt<T, U...>::build(Span<T>  buf,
                                  usz      seg,
                                  const V &arg,
                                  const W &...args) const noexcept {
    usz n  = build(buf, seg);
    n     += fmt(buf.span(n), arg);
    return n + build(buf.span(n), seg + 1, args...);
}

} // namespace impl

} // namespace srr

#endif // SRR_IMPL_FMT_HPP_
