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

#ifndef SRR_IMPL_REF_HPP_
#define SRR_IMPL_REF_HPP_

inline namespace srr {
namespace impl {

template<typename T> class Ref {
public:
    // NOLINTNEXTLINE(readability-identifier-naming)
    using val_t = T;

    constexpr Ref() noexcept;
    constexpr Ref(T &val) noexcept;

    constexpr                  operator T &() const noexcept;

    [[nodiscard]] constexpr T &get() const noexcept;

private:
    T *p_;
};

// === impl ===

template<typename T> constexpr Ref<T>::Ref() noexcept : p_{ nullptr } {}

template<typename T> constexpr Ref<T>::Ref(T &val) noexcept : p_{ &val } {}

template<typename T> constexpr Ref<T>::operator T &() const noexcept {
    return *p_;
}

template<typename T> constexpr T &Ref<T>::get() const noexcept { return *p_; }

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_REF_HPP_
