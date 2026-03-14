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
    TRACE,
    INFO,
    DBG,
    WARN,
    ERR,
    PAN,
};

template<Type T> constexpr strv  TYPE_STR;
template<> inline constexpr strv TYPE_STR<Type::TRACE> = {};
template<> inline constexpr strv TYPE_STR<Type::INFO>  = SRR_BLUE("Info") ": ";
template<> inline constexpr strv TYPE_STR<Type::DBG>  = SRR_GREEN("Debug") ": ";
template<> inline constexpr strv TYPE_STR<Type::WARN> = SRR_YELLOW("Warn") ": ";
template<> inline constexpr strv TYPE_STR<Type::ERR>  = SRR_RED("Err") ": ";
template<> inline constexpr strv TYPE_STR<Type::PAN>  = SRR_RED("Panic") ": ";

template<Type T, typename... U>
    requires(StrFmtable<U> && ...)
void log(const fmt_str<no_deduce_t<U>...> &fmt, U &&...args) {
    const strb buf  = impl::fmt_buf;

    usize      n    = buf.copy(TYPE_STR<T>);

    n              += fmt.apply(buf.span(n), args...);

    buf[n++]        = '\n';
    buf[n]          = '\0';

    sys::write(sys::COUT, buf.span(0, n));
}

} // namespace lm

#endif // LM_LOG_HPP_
