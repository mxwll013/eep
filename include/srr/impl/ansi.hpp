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

#ifndef SRR_IMPL_ANSI_HPP_
#define SRR_IMPL_ANSI_HPP_

#define SRR_IMPL_ANSI(...)         "\033[" __VA_ARGS__ "m"
#define SRR_IMPL_ANSI_RESET        SRR_IMPL_ANSI("0")
#define SRR_IMPL_ANSI_COLOR(c, x)  SRR_IMPL_ANSI(c) x SRR_IMPL_ANSI_RESET

#define SRR_IMPL_ANSI_BLACK(...)   SRR_IMPL_ANSI_COLOR("30", __VA_ARGS__)
#define SRR_IMPL_ANSI_RED(...)     SRR_IMPL_ANSI_COLOR("31", __VA_ARGS__)
#define SRR_IMPL_ANSI_GREEN(...)   SRR_IMPL_ANSI_COLOR("32", __VA_ARGS__)
#define SRR_IMPL_ANSI_YELLOW(...)  SRR_IMPL_ANSI_COLOR("33", __VA_ARGS__)
#define SRR_IMPL_ANSI_BLUE(...)    SRR_IMPL_ANSI_COLOR("34", __VA_ARGS__)
#define SRR_IMPL_ANSI_MAGENTA(...) SRR_IMPL_ANSI_COLOR("35", __VA_ARGS__)
#define SRR_IMPL_ANSI_CYAN(...)    SRR_IMPL_ANSI_COLOR("36", __VA_ARGS__)
#define SRR_IMPL_ANSI_WHITE(...)   SRR_IMPL_ANSI_COLOR("37", __VA_ARGS__)

#endif // SRR_IMPL_ANSI_HPP_
