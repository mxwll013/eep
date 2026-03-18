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

#include "srr/impl/Res.hpp"

#include "srr/ctr.hpp"
#include "srr/str.hpp"
#include "srr/types.hpp"

inline namespace srr {

// NOLINTBEGIN(readability-identifier-naming)

// Exit code
using exitc                    = enum class Exitc : u8;

// Error code
using errc                     = enum class Errc : u8;

// Error
using err                      = class Err;

// Result
template<typename T> using res = impl::Res<T, err>;

// NOLINTEND(readability-identifier-naming)

enum class Exitc : u8 {
    OK,
    FAIL,

    PANIC,
    UNREACHABLE,
    ASSERT,

    SYS,

    EXITC_COUNT,
};

enum class Errc : u8 {
    OK,
    FAIL,

    INVALID_ARG,

    SYS_WRITE_FAIL,
    SYS_MUNMAP_FAIL,

    ERRC_COUNT,
};

[[nodiscard]] constexpr strv  msg(exitc c) noexcept;
[[nodiscard]] constexpr strv  msg(errc c) noexcept;
[[nodiscard]] constexpr exitc cast(errc c) noexcept;

class Err {
public:
    constexpr Err() noexcept;
    constexpr Err(errc c) noexcept;
    constexpr Err(strv msg) noexcept;
    constexpr Err(strv msg, errc c) noexcept;

    constexpr bool               operator!() const noexcept;
    constexpr                    operator bool() const noexcept;

    [[nodiscard]] constexpr strv msg() const noexcept;
    [[nodiscard]] constexpr errc code() const noexcept;

private:
    strv msg_;
    errc c_;
};

// === impl ===

static constexpr usz EXITC_COUNT = static_cast<usz>(exitc::EXITC_COUNT);
static constexpr usz ERRC_COUNT  = static_cast<usz>(errc::ERRC_COUNT);

static constexpr arr<strv, EXITC_COUNT> STR_EXITC = {
    "Ok", "Fail", "Panic", "Unreachable", "Assertion fail", "System error",
};

static constexpr arr<strv, ERRC_COUNT> STR_ERRC = {
    "Ok", "Fail", "Invalid argument.", "Failed on write.", "Failed on unmap.",
};

static constexpr arr<exitc, ERRC_COUNT> CAST_ERRC = {
    Exitc::OK,   // errc::OK
    Exitc::FAIL, // errc::FAIL

    Exitc::FAIL, // errc::INVALID_ARG

    Exitc::SYS,  // errc::SYS_WRITE_FAIL
    Exitc::SYS,  // errc::SYS_MUNMAP_FAIL
};

constexpr strv  msg(exitc c) noexcept { return STR_EXITC[static_cast<usz>(c)]; }

constexpr strv  msg(errc c) noexcept { return STR_ERRC[static_cast<usz>(c)]; }

constexpr exitc cast(errc c) noexcept { return CAST_ERRC[static_cast<usz>(c)]; }

constexpr Err::Err() noexcept : c_{ errc::OK } {}

constexpr Err::Err(errc c) noexcept : c_{ c } {}

constexpr Err::Err(strv msg) noexcept : msg_{ msg }, c_{ errc::FAIL } {}

constexpr Err::Err(strv msg, errc c) noexcept : msg_{ msg }, c_{ c } {}

constexpr bool Err::operator!() const noexcept { return c_ == errc::OK; }

constexpr Err::operator bool() const noexcept { return c_ != errc::OK; }

constexpr strv Err::msg() const noexcept { return msg_; }

constexpr errc Err::code() const noexcept { return c_; }

} // namespace srr

#endif // SRR_ERR_HPP_
