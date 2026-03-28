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

#ifndef SRR_IMPL_ERR_HPP_
#define SRR_IMPL_ERR_HPP_

#include "srr/ctr.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

class Ter {
public:
    // NOLINTNEXTLINE(cppcoreguidelines-use-enum-class)
    enum Code : u8 {
        OK,
        FAIL,

        PANIC,
        UNREACH,
        CHECK,

        SYS,
        CLI,

        TERC_COUNT,
    };

    constexpr Ter() noexcept;
    constexpr Ter(Code c) noexcept;

    constexpr bool               operator!() const noexcept;
    constexpr                    operator bool() const noexcept;

    [[nodiscard]] constexpr strv msg() const noexcept;
    [[nodiscard]] constexpr Code code() const noexcept;

    constexpr bool               operator==(Ter e) const noexcept;
    constexpr bool               operator==(Code c) const noexcept;

private:
    Code c_;
};

class Err {
public:

    // NOLINTNEXTLINE(cppcoreguidelines-use-enum-class)
    enum Code : u8 {
        OK,
        FAIL,

        INVALID_ARG,
        NOT_FOUND,

        SYS_WRITE_FAIL,
        SYS_MUNMAP_FAIL,

        CLI_BAD_USAGE,
        CLI_TOO_MANY_ARGS,
        CLI_BAD_CMD,
        CLI_BAD_FLAG,
        CLI_BAD_SHORTHAND,
        CLI_UNARY_DASH,

        ERRC_COUNT,
    };

    // NOLINTNEXTLINE(readability-identifier-naming)
    using alias_t = Code;

    constexpr Err() noexcept;
    constexpr Err(Code c) noexcept;
    constexpr Err(strv tr) noexcept;
    constexpr Err(strv tr, Code c) noexcept;

    constexpr bool               operator!() const noexcept;
    constexpr                    operator bool() const noexcept;

    [[nodiscard]] constexpr strv trace() const noexcept;
    [[nodiscard]] constexpr strv msg() const noexcept;
    [[nodiscard]] constexpr Code code() const noexcept;
    [[nodiscard]] constexpr Ter  ter() const noexcept;

    constexpr bool               operator==(Err e) const noexcept;
    constexpr bool               operator==(Code c) const noexcept;

private:
    strv tr_;
    Code c_;
};

// === impl ===

static constexpr usz TERC_COUNT = static_cast<usz>(Ter::Code::TERC_COUNT);
static constexpr usz ERRC_COUNT = static_cast<usz>(Err::Code::ERRC_COUNT);

static constexpr arr<strv, TERC_COUNT> STR_TERC = {
    "Ok",          "Generic error", "Generic panic", "Unreach panic",
    "Check panic", "System error",  "CLI error",
};

static constexpr arr<strv, ERRC_COUNT> STR_ERRC = {
    "Ok",
    "Fail",

    "Invalid argument.",
    "Not found.",

    "Failed on write.",
    "Failed on unmap.",

    "Invalid usage.",
    "Too many arguments.",
    "Unknown command.",
    "Unknown flag.",
    "Unknown shorthand flag.",
    "Unary dash '-' is not a valid flag.",
};

static constexpr arr<Ter::Code, ERRC_COUNT> ERRC_2_TERC = {
    Ter::OK,   // Err::OK
    Ter::FAIL, // Err::FAIL

    Ter::FAIL, // Err::INVALID_ARG
    Ter::FAIL, // Err::NOT_FOUND

    Ter::SYS,  // Err::SYS_WRITE_FAIL
    Ter::SYS,  // Err::SYS_MUNMAP_FAIL

    Ter::CLI,  // Err::CLI_BAD_USAGE
    Ter::CLI,  // Err::CLI_TOO_MANY_ARGS
    Ter::CLI,  // Err::CLI_BAD_CMD
    Ter::CLI,  // Err::CLI_BAD_FLAG
    Ter::CLI,  // Err::CLI_BAD_SHORTHAND
    Ter::CLI,  // Err::CLI_UNARY_DASH
};

constexpr Ter::Ter() noexcept : c_{ OK } {}

constexpr Ter::Ter(Code c) noexcept : c_{ c } {}

constexpr bool Ter::operator!() const noexcept { return c_ == OK; }

constexpr Ter::operator bool() const noexcept { return c_ != OK; }

constexpr strv Ter::msg() const noexcept {
    return STR_TERC[static_cast<usz>(c_)];
}

constexpr Ter::Code Ter::code() const noexcept { return c_; }

constexpr bool      Ter::operator==(Ter e) const noexcept { return c_ == e.c_; }

constexpr bool      Ter::operator==(Code c) const noexcept { return c_ == c; }

constexpr Err::Err() noexcept : c_{ OK } {}

constexpr Err::Err(Code c) noexcept : c_{ c } {}

constexpr Err::Err(strv tr) noexcept : tr_{ tr }, c_{ FAIL } {}

constexpr Err::Err(strv tr, Code c) noexcept : tr_{ tr }, c_{ c } {}

constexpr bool Err::operator!() const noexcept { return c_ == OK; }

constexpr Err::operator bool() const noexcept { return c_ != OK; }

constexpr strv Err::trace() const noexcept { return tr_; }

constexpr strv Err::msg() const noexcept {
    return STR_ERRC[static_cast<usz>(c_)];
}

constexpr Err::Code Err::code() const noexcept { return c_; }

constexpr Ter       Err::ter() const noexcept {
    return ERRC_2_TERC[static_cast<usz>(c_)];
}

constexpr bool Err::operator==(Err e) const noexcept { return c_ == e.c_; }

constexpr bool Err::operator==(Code c) const noexcept { return c_ == c; }

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_ERR_HPP_
