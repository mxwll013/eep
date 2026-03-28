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

#include <lm/macros.hpp>
#include <srr/types.hpp>

i32 main() noexcept {
    LM_LOG("Bare");
    LM_INFO("Information");
    LM_TRC("Trace");
    LM_DBG("Debug");
    LM_WARN("Warning");
    LM_ERR("Error");
    LM_PAN("Panic");

    LM_QRY("Query");

    LM_TERM();
}
