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
#include "srr/impl/Fmter.hpp"
#include "srr/impl/Span.hpp"
#include "srr/impl/traits.hpp"

#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T, typename U>
concept Fmtable = requires(Fmter<T> &buf, const U &u) {
    { fmt(buf, u) } noexcept -> Same<void>;
};

struct Seg {
    usz start;
    usz end;
};

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
class Fmt {
public:
    template<usz M> consteval Fmt(const T (&p)[M]) noexcept;

    constexpr void apply(Fmter<T> &buf, const U &...args) const noexcept;

private:
    static constexpr usz N = sizeof...(U);

    Span<const T>        str_{};
    Arr<Seg, N + 1>      segs_{};

    consteval void       parse();

    constexpr void       seg(Fmter<T> &buf, usz i) const noexcept;

    template<usz... I>
    constexpr void build(Fmter<T> &buf,
                         idx_seq<I...> /*unused*/,
                         const U &...args) const noexcept;
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
constexpr void Fmt<T, U...>::apply(Fmter<T> &buf,
                                   const U &...args) const noexcept {
    return build(buf, mk_idx_seq_for_t<U...>{}, args...);
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
consteval void Fmt<T, U...>::parse() {
    usz n    = 0;
    usz last = 0;

    for (usz i = 0; i < str_.len(); i++) {
        if (str_[i] == '}') throw "Unmatched '}'!";
        if (str_[i] != '{') continue;
        ++i;

        if (i >= str_.len()) throw "Unexpected end after '{'!";

        if (str_[i] == '{') continue;

        if (str_[i] != '}') throw "Expected '}' after '{'!";

        if (n >= N) throw "Too many format specifiers!";

        segs_[n++] = { last, i - 1 };
        last       = i + 1;
    }

    if (n != N) throw "Wrong number of arguments!";

    segs_[n] = { last, str_.len() };
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
constexpr void Fmt<T, U...>::seg(Fmter<T> &buf, usz i) const noexcept {
    buf.push(str_.span(segs_[i].start, segs_[i].end));
}

template<typename T, typename... U>
    requires(Fmtable<T, U> && ...)
template<usz... I>
constexpr void Fmt<T, U...>::build(Fmter<T> &buf,
                                   idx_seq<I...> /*unused*/,
                                   const U &...args) const noexcept {
    ((seg(buf, I), fmt(buf, args)), ...);
    seg(buf, N);
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_FMT_HPP_
