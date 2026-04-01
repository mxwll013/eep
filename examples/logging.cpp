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
    LM_LOG("Bare log");
    LM_INFO("Info log");
    LM_TRC("Trace log");
    LM_DBG("Debug log");
    LM_WARN("Warning log");
    LM_ERR("Error log");
    LM_PAN("Panic log");

    LM_QRY("Bare query");
    LM_QRY_INFO("Info query");
    LM_QRY_TRC("Trace query");
    LM_QRY_DBG("Debug query");
    LM_QRY_WARN("Warning query");
    LM_QRY_ERR("Error query");
    LM_QRY_PAN("Panic query");
}
