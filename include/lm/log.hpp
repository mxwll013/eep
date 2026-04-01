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
    requires(StrFmtable<U> && ...)
void log(const fmt_str<no_deduce_t<U>...> &fmt, U &&...args) {
    const strb buf  = impl::fmt_buf;

    usz        n    = buf.copy(TYPE_STR<T>);

    n              += fmt.apply(buf.span(n), args...);

    buf[n++]        = '\n';
    buf[n]          = '\0';

    sys::write(TYPE_FD<T>, buf.span(0, n));
}

template<Type T, typename... U>
    requires(StrFmtable<U> && ...)
bool query(const fmt_str<no_deduce_t<U>...> &fmt, U &&...args) {
    const strb buf  = impl::fmt_buf;

    usz        n    = buf.copy(TYPE_STR<T>);

    n              += fmt.apply(buf.span(n), args...);

    n              += buf.span(n).copy("? (y/n) \0");

    sys::write(TYPE_FD<T>, buf.span(0, n));

    // TODO: read input

    return true;
}

} // namespace lm

#endif // LM_LOG_HPP_
