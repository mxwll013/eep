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

#include "chrl/cli.hpp"

#include "chrl/syntax.hpp"

#include <lm/macros.hpp>
#include <srr/ctr.hpp>
#include <srr/err.hpp>
#include <srr/str.hpp>
#include <srr/types.hpp>

namespace chrl {
namespace {

err versionHook(const Ctx &ctx) noexcept {
    const Cli &cli = ctx.cli();
    LM_LOG("{} v{}.{} ({})",
           cli.root.get().name,
           cli.ver_maj,
           cli.ver_min,
           strv{ cli.dbg ? "debug" : "release" });
    return {};
}

err helpHook(const Ctx &ctx) noexcept {
    LM_DBG("TODO: help msg");
    (void) ctx;
    return {};
}

constexpr Cmd CMD_VERSION{
    .name = "version",
    .desc = "Show version info.",
    .hook = versionHook,
};

constexpr Cmd CMD_HELP{
    .name = "help",
    .desc = "Show usage info.",
    .hook = helpHook,
};

constexpr CmdArr<2> BUILTINS{ CMD_VERSION, CMD_HELP };

void setFlag(u64 &flags, FlagId id) noexcept { flags |= (1_u64 << id); }

bool getFlag(u64 flags, FlagId id) noexcept {
    return (flags & (1_u64 << id)) != 0;
}

template<typename T>
res<cref<T>> fuzzy(span<const cref<T>> ctr, strv s) noexcept {
    for (const cref<T> &ele : ctr)
        if (s == ele.get().name) return ele;

    return err::NOT_FOUND;
}

list<strv> handle(i32 argc, char **argv) noexcept {
    const usz  n = static_cast<usz>(argc);
    list<strv> args{ n - 1 };
    for (usz i = 1; i < n; ++i) args.empl(argv[i]);
    return args;
}

void handleBuiltin(Parsed &parsed, strv v) noexcept {
    const res<cref<Cmd>> r = fuzzy(BUILTINS.span(), v);

    if (r.ok()) {
        parsed.path.empl(r.unwrap());
        parsed.builtin = true;
    }
}

void handleParg(Parsed &parsed, strv parg) noexcept {
    const Cmd &cmd = parsed.path.last().get();

    if (cmd.pargs.len() == parsed.pargs.len()) {
        parsed.err = { parg, err::CLI_TOO_MANY_ARGS };
        return;
    }

    parsed.pargs.empl(parg);
}

void handleWord(Parsed &parsed, strv word) noexcept {
    const Cmd &cmd = parsed.path.last().get();

    handleBuiltin(parsed, word);
    if (parsed.builtin) return;

    if (cmd.subs.empty()) {
        handleParg(parsed, word);
        return;
    }

    const res<cref<Cmd>> r = fuzzy(cmd.subs, word);

    if (r.ok()) {
        parsed.path.empl(r.unwrap());
        return;
    }

    if (cmd.hook != nullptr) {
        handleParg(parsed, word);
        return;
    }

    parsed.err = { word, err::CLI_BAD_CMD };
}

void handleFlag(const Cli &cli, Parsed &parsed, strv flag) noexcept {
    if (flag.len() == 1) {
        parsed.err = err::CLI_UNARY_DASH;
        return;
    }

    if (flag[1] == '-') {
        flag = flag.span(2);

        handleBuiltin(parsed, flag);
        if (parsed.builtin) return;

        const res<cref<Flag>> r = fuzzy(cli.flags, flag);

        if (r.ok()) {
            setFlag(parsed.flags, r.unwrap().get().id);
            return;
        }

        parsed.err = { flag, err::CLI_BAD_FLAG };
        return;
    }

    flag = flag.span(1);

    for (usz i = 0; i < flag.len(); ++i) {
        bool found = false;

        for (const Flag &f : cli.flags) {
            if (flag[i] != f.shrt) continue;
            setFlag(parsed.flags, f.id);
            found = true;
            break;
        }

        if (!found) {
            parsed.err = { flag.span(i, i + 1), err::CLI_BAD_SHORTHAND };
            return;
        }
    }
}

Parsed parse(const Cli &cli, const list<strv> &args) noexcept {
    Parsed parsed{
        .args = args,
        .path{},
        .pargs{},
        .err{},
        .flags   = 0,
        .builtin = false,
    };
    parsed.path.empl(cli.root);

    for (const strv &arg : args) {
        if (arg.first() != '-')
            handleWord(parsed, arg);
        else
            handleFlag(cli, parsed, arg);

        if (parsed.builtin || parsed.err) return parsed;
    }

    const Cmd &cmd = parsed.path.last().get();

    if (cmd.hook == nullptr) parsed.err = { cmd.name, err::CLI_BAD_USAGE };

    return parsed;
}

[[noreturn]] void done(const err &e) noexcept {
    if (e == err::CLI_BAD_USAGE) LM_DBG("TODO : usage msg");
    LM_TERM(e);
}

} // namespace

Ctx::Ctx(const Cli &cli, const list<strv> &args) noexcept : cli_{ cli } {
    parsed_ = parse(cli, args);
}

bool Ctx::flag(FlagId id) const noexcept { return getFlag(parsed_.flags, id); }

bool Ctx::ok() const noexcept { return !parsed_.err; }

const err &Ctx::err() const noexcept { return parsed_.err; }

const Cli &Ctx::cli() const noexcept { return cli_; }

Hook       Ctx::hook() const noexcept { return parsed_.path.last().get().hook; }

void       entry(const Cli &cli, i32 argc, char **argv) noexcept {
    const list<strv> args = handle(argc, argv);

    const Ctx        ctx  = { cli, args };

    if (!ctx.ok()) done(ctx.err());

    done(ctx.hook()(ctx));
}

} // namespace chrl
