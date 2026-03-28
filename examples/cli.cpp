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

#include <chrl/cli.hpp>
#include <chrl/syntax.hpp>
#include <lm/macros.hpp>
#include <srr/err.hpp>

using namespace chrl;

namespace {

// err rootHook([[maybe_unused]] const Ctx &ctx) noexcept {
//     LM_DBG("root hook called!");
//     return {};
// }

err helloHook([[maybe_unused]] const Ctx &ctx) noexcept {
    LM_DBG("hello hook called!");
    return {};
}

} // namespace

constexpr Cmd CMD_HELLO{
    .name = "hello",
    .desc = "A simple hello world command.",
    .hook = helloHook,
};

constexpr CmdArr<1> CMD_ROOT_SUBS{ CMD_HELLO };

constexpr Cmd       CMD_ROOT{
          .name = "cli",
          .desc = "A simple CLI example.",
          .subs = CMD_ROOT_SUBS,
          .hook = nullptr,
};

constexpr Cli CLI{
    .root    = CMD_ROOT,
    .ver_maj = 1,
    .ver_min = 2,
};

CHRL_ENTRY(CLI)
