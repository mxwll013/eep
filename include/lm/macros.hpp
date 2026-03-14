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

#include "lm/log.hpp"   // IWYU pragma: export
#include "lm/panic.hpp" // IWYU pragma: export

#define LM_LOG(...)  ::lm::log<::lm::Type::TRACE>(__VA_ARGS__)
#define LM_INFO(...) ::lm::log<::lm::Type::INFO>(__VA_ARGS__)
#define LM_WARN(...) ::lm::log<::lm::Type::WARN>(__VA_ARGS__)
#define LM_ERR(...)  ::lm::log<::lm::Type::ERR>(__VA_ARGS__)
#define LM_PAN(...)  ::lm::log<::lm::Type::PAN>(__VA_ARGS__)

#define LM_EXIT(...) ::lm::exit(__VA_ARGS__)

#ifndef BRV_RELEASE

    #define LM_DBG(...) ::lm::log<::lm::Type::DBG>(__VA_ARGS__)

    #define LM_PANIC(...)                                                      \
        ::lm::panic(::lm::Trace{ __FILE__, __LINE__ } __VA_OPT__(, )           \
                        __VA_ARGS__)
    #define LM_UNREACH(...)                                                    \
        ::lm::unreach(::lm::Trace{ __FILE__, __LINE__ } __VA_OPT__(, )         \
                          __VA_ARGS__)
    #define LM_ASSERT(c, ...)                                                  \
        ::lm::runassert(::lm::Trace{ __FILE__, __LINE__ },                     \
                        (c),                                                   \
                        #c __VA_OPT__(, ) __VA_ARGS__)
#else

    #define LM_DBG(...)     ((void) 0)

    #define LM_ASSERT(...)  ::lm::runassert(__VA_ARGS__)
    #define LM_UNREACH(...) ::lm::unreach(__VA_ARGS__)
    #define LM_PANIC(...)   ::lm::panic(__VA_ARGS__)
#endif

#endif // LM_MACROS_HPP_
