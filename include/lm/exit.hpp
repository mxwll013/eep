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

#ifndef LM_EXIT_HPP_
#define LM_EXIT_HPP_

#include <srr/err.hpp>
#include <srr/str.hpp>

namespace lm {

[[noreturn]] void exit(err e) noexcept;
[[noreturn]] void exit(exitc c) noexcept;

void              assert(bool c) noexcept;
void              assert(bool c, strv msg) noexcept;

} // namespace lm

#endif // LM_EXIT_HPP_
