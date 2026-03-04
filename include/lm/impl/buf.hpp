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

#ifndef LM_IMPL_BUF_HPP_
#define LM_IMPL_BUF_HPP_

#include <srr/ctr.hpp>
#include <srr/types.hpp>

namespace lm::impl {

static constexpr usize BUF_LEN = 1024;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static thread_local arr<char, BUF_LEN> fmt_buf;

} // namespace lm::impl

#endif // LM_IMPL_BUF_HPP_
