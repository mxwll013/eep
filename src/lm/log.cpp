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

#include "lm/log.hpp"

#include <srr/str.hpp>
#include <srr/sys.hpp>

namespace lm {

void log(strv msg) noexcept { sys::write(sys::COUT, msg); }

} // namespace lm
