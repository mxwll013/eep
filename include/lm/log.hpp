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
#include <srr/sys.hpp>
#include <srr/traits.hpp>
#include <srr/types.hpp>

namespace lm {

template<typename... U>
    requires(CharFormattable<U> && ...)
void log(const fmt_str<no_deduce_t<U>...> &fmt, U &&...args) {
    usize n            = fmt.apply(impl::fmt_buf, args...);

    impl::fmt_buf[n++] = '\n';
    impl::fmt_buf[n]   = '\0';

    sys::write(sys::COUT, impl::fmt_buf.span(0, n));
}

} // namespace lm

#endif // LM_LOG_HPP_
