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

#ifndef SRR_IMPL_RES_HPP_
#define SRR_IMPL_RES_HPP_

#include "srr/mem.hpp"
#include "srr/traits.hpp"

inline namespace srr {
namespace impl {

template<typename T, typename E> class Res {
public:
    constexpr Res(const Res &) noexcept            = delete;
    constexpr Res &operator=(const Res &) noexcept = delete;
    constexpr Res &operator=(Res &&) noexcept      = delete;

    constexpr Res(Res &&r) noexcept;
    constexpr Res(const alias_t<E> &err) noexcept;
    constexpr Res(alias_t<E> &&err) noexcept;
    constexpr Res(const E &err) noexcept;
    constexpr Res(E &&err) noexcept;
    constexpr Res(const T &val) noexcept;
    constexpr Res(T &&val) noexcept;
    constexpr ~Res() noexcept;

    [[nodiscard]] constexpr bool     ok() const noexcept;
    [[nodiscard]] constexpr bool     bad() const noexcept;

    [[nodiscard]] constexpr E       &err()       &noexcept;
    [[nodiscard]] constexpr const E &err() const & noexcept;
    [[nodiscard]] constexpr E      &&err()      &&noexcept;
    [[nodiscard]] constexpr T       &unwrap()       &noexcept;
    [[nodiscard]] constexpr const T &unwrap() const & noexcept;
    [[nodiscard]] constexpr T      &&unwrap()      &&noexcept;

private:
    bool ok_;

    union Union {
        T val;
        E err;

        constexpr Union() noexcept {}

        constexpr ~Union() noexcept {}

        constexpr Union(const Union &) noexcept            = delete;
        constexpr Union(Union &&) noexcept                 = delete;
        constexpr Union &operator=(const Union &) noexcept = delete;
        constexpr Union &operator=(Union &&) noexcept      = delete;

    } u_;
};

// === Impl ===

template<typename T, typename E>
constexpr Res<T, E>::Res(Res &&r) noexcept : ok_{ r.ok_ } {
    if (ok_)
        mem::construct(&u_.val, mv(r.u_.val));
    else
        mem::construct(&u_.err, mv(r.u_.err));
}

template<typename T, typename E>
constexpr Res<T, E>::Res(const alias_t<E> &err) noexcept : ok_{ false } {
    mem::construct(&u_.err, err);
}

template<typename T, typename E>
constexpr Res<T, E>::Res(alias_t<E> &&err) noexcept : ok_{ false } {
    mem::construct(&u_.err, mv(err));
}

template<typename T, typename E>
constexpr Res<T, E>::Res(const E &err) noexcept : ok_{ false } {
    mem::construct(&u_.err, err);
}

template<typename T, typename E>
constexpr Res<T, E>::Res(E &&err) noexcept : ok_{ false } {
    mem::construct(&u_.err, mv(err));
}

template<typename T, typename E>
constexpr Res<T, E>::Res(const T &val) noexcept : ok_{ true } {
    mem::construct(&u_.val, val);
}

template<typename T, typename E>
constexpr Res<T, E>::Res(T &&val) noexcept : ok_{ true } {
    mem::construct(&u_.val, mv(val));
}

template<typename T, typename E> constexpr Res<T, E>::~Res() noexcept {
    if (ok_)
        mem::destruct(&u_.val);
    else
        mem::destruct(&u_.err);
}

template<typename T, typename E> constexpr bool Res<T, E>::ok() const noexcept {
    return ok_;
}

template<typename T, typename E>
constexpr bool Res<T, E>::bad() const noexcept {
    return !ok_;
}

template<typename T, typename E> constexpr E &Res<T, E>::err() & noexcept {
    return u_.err;
}

template<typename T, typename E>
constexpr const E &Res<T, E>::err() const & noexcept {
    return u_.err;
}

template<typename T, typename E> constexpr E &&Res<T, E>::err() && noexcept {
    return mv(u_.err);
}

template<typename T, typename E> constexpr T &Res<T, E>::unwrap() & noexcept {
    return u_.val;
}

template<typename T, typename E>
constexpr const T &Res<T, E>::unwrap() const & noexcept {
    return u_.val;
}

template<typename T, typename E> constexpr T &&Res<T, E>::unwrap() && noexcept {
    return mv(u_.val);
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_RES_HPP_
