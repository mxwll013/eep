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

#ifndef SRR_ERR_HPP_
#define SRR_ERR_HPP_

#include "srr/ctr.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

using exitc = enum class Exitc : u8;
using errc  = enum class Errc : u8;
using err   = class Err;

// NOLINTEND(readability-identifier-naming)

enum class Exitc : u8 {
    OK,
    FAIL,

    ASSERT,

    SYS,

    EXITC_COUNT,
};

enum class Errc : u8 {
    OK,
    FAIL,

    SYS_WRITE_FAIL,

    ERRC_COUNT,
};

[[nodiscard]] constexpr exitc cast(errc c) noexcept;

[[nodiscard]] constexpr strv  fmt(exitc c) noexcept;
[[nodiscard]] constexpr strv  fmt(errc c) noexcept;
[[nodiscard]] constexpr strv  fmt(err e) noexcept;

class Err {
public:
    [[nodiscard]] constexpr Err() noexcept;
    [[nodiscard]] constexpr Err(errc c) noexcept;

    [[nodiscard]] constexpr errc  get() const noexcept;
    [[nodiscard]] constexpr exitc cast() const noexcept;

    [[nodiscard]] constexpr       operator bool() noexcept;

private:
    errc c_;
};

// === impl ===

static constexpr usize EXITC_COUNT = static_cast<usize>(exitc::EXITC_COUNT);
static constexpr usize ERRC_COUNT  = static_cast<usize>(errc::ERRC_COUNT);

static constexpr arr<strv, EXITC_COUNT> STR_EXITC = {
    "Ok",
    "Fail",

    "Assertion error",

    "System error",
};

static constexpr arr<strv, ERRC_COUNT> STR_ERRC = {
    "Ok",
    "Fail",

    "[sys] Failed on write.",
};

static constexpr arr<exitc, ERRC_COUNT> CAST_ERRC = {
    Exitc::OK,   // errc::OK
    Exitc::FAIL, // errc::FAIL

    Exitc::SYS,  // errc::SYS_WRITE_FAIL
};

constexpr exitc cast(errc c) noexcept {
    return CAST_ERRC[static_cast<usize>(c)];
}

constexpr strv fmt(exitc c) noexcept {
    return STR_EXITC[static_cast<usize>(c)];
}

constexpr strv fmt(errc c) noexcept { return STR_ERRC[static_cast<usize>(c)]; }

constexpr strv fmt(err e) noexcept { return fmt(e.get()); }

constexpr Err::Err() noexcept : c_{ errc::OK } {}

constexpr Err::Err(errc c) noexcept : c_{ c } {}

constexpr errc  Err::get() const noexcept { return c_; }

constexpr exitc Err::cast() const noexcept { return ::cast(c_); }

constexpr Err:: operator bool() noexcept { return c_ != errc::OK; }

} // namespace srr

#endif // SRR_ERR_HPP_
