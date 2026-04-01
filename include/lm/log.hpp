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

#ifndef LM_LOG_HPP_
#define LM_LOG_HPP_

#include "lm/impl/buf.hpp"

#include "srr/err.hpp"

#include <srr/fmt.hpp>
#include <srr/str.hpp>
#include <srr/sys.hpp>
#include <srr/traits.hpp>
#include <srr/types.hpp>

namespace lm {

enum class Type : u8 {
    BARE,
    INFO,
    TRC,
    DBG,
    WARN,
    ERR,
    PAN,
};

template<Type T> constexpr sys::fd  TYPE_FD             = {};
template<> inline constexpr sys::fd TYPE_FD<Type::BARE> = sys::COUT;
template<> inline constexpr sys::fd TYPE_FD<Type::INFO> = sys::COUT;
template<> inline constexpr sys::fd TYPE_FD<Type::TRC>  = sys::COUT;
template<> inline constexpr sys::fd TYPE_FD<Type::DBG>  = sys::COUT;
template<> inline constexpr sys::fd TYPE_FD<Type::WARN> = sys::CERR;
template<> inline constexpr sys::fd TYPE_FD<Type::ERR>  = sys::CERR;
template<> inline constexpr sys::fd TYPE_FD<Type::PAN>  = sys::CERR;

template<Type T> constexpr strv     TYPE_STR;
template<> inline constexpr strv    TYPE_STR<Type::BARE> = {};
template<> inline constexpr strv TYPE_STR<Type::INFO> = SRR_BLUE("Info") ":  ";
template<> inline constexpr strv TYPE_STR<Type::TRC>  = SRR_CYAN("Trace") ": ";
template<> inline constexpr strv TYPE_STR<Type::DBG>  = SRR_GREEN("Debug") ": ";
template<>
inline constexpr strv TYPE_STR<Type::WARN>           = SRR_YELLOW("Warn") ":  ";
template<> inline constexpr strv TYPE_STR<Type::ERR> = SRR_RED("Err") ":   ";
template<> inline constexpr strv TYPE_STR<Type::PAN> = SRR_RED("Panic") ": ";

template<Type T, typename... U>
    requires(Fmtable<U> && ...)
void log(const fmt_str<no_deduce_t<U>...> &fmt, U &&...args) {
    fmter out = impl::fmt_buf.span();

    out.push(TYPE_STR<T>);

    fmt.apply(out, args...);

    out.push("\n\0");

    const res<strv> r = out.done();

    if (r.ok()) sys::write(TYPE_FD<T>, r.unwrap());
}

template<Type T, typename... U>
    requires(Fmtable<U> && ...)
bool query(const fmt_str<no_deduce_t<U>...> &fmt, U &&...args) {
    fmter      out = impl::fmt_buf.span();
    const strb in  = impl::query_buf;

    out.push(TYPE_STR<T>);

    fmt.apply(out, args...);

    out.push("? (y/n) \0");

    const res<strv> r = out.done();

    if (r.bad()) return false;

    sys::write(TYPE_FD<T>, r.unwrap());

    sys::read(sys::CIN, in);

    switch (in[0]) {
    case '\n': [[fallthrough]];
    case 'y' : [[fallthrough]];
    case 'Y' : return true;
    default  : return false;
    }
}

} // namespace lm

#endif // LM_LOG_HPP_
