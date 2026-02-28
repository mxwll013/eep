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

#ifndef LM_MACROS_HPP_
#define LM_MACROS_HPP_

#include "lm/exit.hpp" // IWYU pragma: export
#include "lm/log.hpp"  // IWYU pragma: export

#ifndef BRV_RELEASE
    #define LM_ASSERT(...) lm::assert(__VA_ARGS__)
#else
    #define LM_ASSERT(...)
#endif

#endif // LM_MACROS_HPP_
