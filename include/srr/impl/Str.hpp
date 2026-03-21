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

#ifndef SRR_IMPL_STR_HPP_
#define SRR_IMPL_STR_HPP_

#include "srr/impl/Alloc.hpp"
#include "srr/impl/Span.hpp"

#include "srr/alg.hpp"
#include "srr/mem.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T, Alloc A> class Str {
public:
    // NOLINTBEGIN(readability-identifier-naming)
    using val_t = T;
    using alloc_t = A;
    // NOLINTEND(readability-identifier-naming)

    constexpr Str() noexcept;
    constexpr Str(usz cap) noexcept;
    constexpr Str(Span<const T> span) noexcept;
    constexpr Str(const Str &other) noexcept;
    constexpr Str(Str &&other) noexcept;

    constexpr Str &operator=(const Str &other) noexcept;
    constexpr Str &operator=(Str &&other) noexcept;

    constexpr ~Str() noexcept;

    constexpr                        operator Span<const T>() const noexcept;
    constexpr                        operator Span<T>() noexcept;

    [[nodiscard]] constexpr usz      len() const noexcept;
    [[nodiscard]] constexpr usz      cap() const noexcept;
    [[nodiscard]] constexpr bool     empty() const noexcept;

    [[nodiscard]] constexpr const T &operator[](usz i) const noexcept;
    [[nodiscard]] constexpr T       &operator[](usz i) noexcept;
    [[nodiscard]] constexpr const T &first() const noexcept;
    [[nodiscard]] constexpr T       &first() noexcept;
    [[nodiscard]] constexpr const T &last() const noexcept;
    [[nodiscard]] constexpr T       &last() noexcept;

    [[nodiscard]] constexpr const T *data() const noexcept;
    [[nodiscard]] constexpr T       *data() noexcept;
    [[nodiscard]] constexpr const T *begin() const noexcept;
    [[nodiscard]] constexpr T       *begin() noexcept;
    [[nodiscard]] constexpr const T *end() const noexcept;
    [[nodiscard]] constexpr T       *end() noexcept;

    constexpr usz                    copy(Span<const T> src) noexcept;

    [[nodiscard]] constexpr Span<const T>  head(usz n) const noexcept;
    [[nodiscard]] constexpr Span<T>        head(usz n) noexcept;
    [[nodiscard]] constexpr Span<const T>  tail(usz n) const noexcept;
    [[nodiscard]] constexpr Span<T>        tail(usz n) noexcept;
    [[nodiscard]] constexpr Span<const T>  span(usz s, usz e) const noexcept;
    [[nodiscard]] constexpr Span<T>        span(usz s, usz e) noexcept;
    [[nodiscard]] constexpr Span<const T>  span(usz s) const noexcept;
    [[nodiscard]] constexpr Span<T>        span(usz s) noexcept;
    [[nodiscard]] constexpr Span<const T>  span() const noexcept;
    [[nodiscard]] constexpr Span<T>        span() noexcept;

    constexpr void                         cls() noexcept;
    constexpr void                         free() noexcept;
    constexpr void                         res(usz cap) noexcept;
    constexpr void                         ensure(usz len) noexcept;

    template<typename... U> constexpr void emplace(U &&...args) noexcept;
    constexpr void                         push(const T &val) noexcept;
    constexpr void                         push(T &&val) noexcept;
    constexpr void                         pop() noexcept;

    [[nodiscard]] constexpr usz  find(Span<const T> sub) const noexcept;
    [[nodiscard]] constexpr usz  find(const T &val) const noexcept;

    [[nodiscard]] constexpr bool prefix(Span<const T> pre) const noexcept;
    [[nodiscard]] constexpr bool suffix(Span<const T> suf) const noexcept;
    [[nodiscard]] constexpr bool contains(Span<const T> sub) const noexcept;
    [[nodiscard]] constexpr bool contains(const T &val) const noexcept;

private:
    A   alloc_;
    T  *arr_;
    usz len_;
    usz cap_;
};

// === impl ===

template<typename T, Alloc A>
constexpr Str<T, A>::Str() noexcept :
    alloc_{},
    arr_{ nullptr },
    len_{ 0 },
    cap_{ 0 } {}

template<typename T, Alloc A>
constexpr Str<T, A>::Str(usz cap) noexcept :
    alloc_{},
    arr_{ alloc_.alloc(cap) },
    len_{ 0 },
    cap_{ cap } {}

template<typename T, Alloc A>
constexpr Str<T, A>::Str(Span<const T> span) noexcept :
    alloc_{},
    arr_{ alloc_.alloc(span.len() + 1) },
    len_{ 0 },
    cap_{ span.len() + 1 } {
    copy(span);
}

template<typename T, Alloc A>
constexpr Str<T, A>::Str(const Str &other) noexcept :
    alloc_{ other.alloc_ },
    arr_{ alloc_.alloc(other.cap_) },
    len_{ 0 },
    cap_{ other.cap_ } {
    copy(other);
}

template<typename T, Alloc A>
constexpr Str<T, A>::Str(Str &&other) noexcept :
    alloc_{ other.alloc_ },
    arr_{ other.arr_ },
    len_{ other.len_ },
    cap_{ other.cap_ } {
    other.arr_ = nullptr;
    other.len_ = 0;
    other.cap_ = 0;
}

template<typename T, Alloc A>
constexpr Str<T, A> &Str<T, A>::operator=(const Str &other) noexcept {
    if (this == &other) return *this;

    cls();
    free();

    alloc_ = other.alloc_;
    arr_   = alloc_.alloc(other.cap_);
    cap_   = other.cap_;

    copy(other);
    return *this;
}

template<typename T, Alloc A>
constexpr Str<T, A> &Str<T, A>::operator=(Str &&other) noexcept {
    if (this == &other) return *this;

    cls();
    free();

    alloc_     = other.alloc_;
    arr_       = other.arr_;
    len_       = other.len_;
    cap_       = other.cap_;

    other.arr_ = nullptr;
    other.len_ = 0;
    other.cap_ = 0;

    return *this;
}

template<typename T, Alloc A> constexpr Str<T, A>::~Str() noexcept {
    if (arr_ == nullptr) return;
    cls();
    free();
}

template<typename T, Alloc A>
constexpr Str<T, A>::operator Span<const T>() const noexcept {
    return { arr_, len_ };
}

template<typename T, Alloc A> constexpr Str<T, A>::operator Span<T>() noexcept {
    return { arr_, len_ };
}

template<typename T, Alloc A> constexpr usz Str<T, A>::len() const noexcept {
    return len_;
}

template<typename T, Alloc A> constexpr usz Str<T, A>::cap() const noexcept {
    return cap_;
}

template<typename T, Alloc A> constexpr bool Str<T, A>::empty() const noexcept {
    return len_ == 0;
}

template<typename T, Alloc A>
constexpr const T &Str<T, A>::operator[](usz i) const noexcept {
    return arr_[i];
}

template<typename T, Alloc A>
constexpr T &Str<T, A>::operator[](usz i) noexcept {
    return arr_[i];
}

template<typename T, Alloc A>
constexpr const T &Str<T, A>::first() const noexcept {
    return arr_[0];
}

template<typename T, Alloc A> constexpr T &Str<T, A>::first() noexcept {
    return arr_[0];
}

template<typename T, Alloc A>
constexpr const T &Str<T, A>::last() const noexcept {
    return arr_[len_ - 1];
}

template<typename T, Alloc A> constexpr T &Str<T, A>::last() noexcept {
    return arr_[len_ - 1];
}

template<typename T, Alloc A>
constexpr const T *Str<T, A>::data() const noexcept {
    return arr_;
}

template<typename T, Alloc A> constexpr T *Str<T, A>::data() noexcept {
    return arr_;
}

template<typename T, Alloc A>
constexpr const T *Str<T, A>::begin() const noexcept {
    return arr_;
}

template<typename T, Alloc A> constexpr T *Str<T, A>::begin() noexcept {
    return arr_;
}

template<typename T, Alloc A>
constexpr const T *Str<T, A>::end() const noexcept {
    return arr_ + len_;
}

template<typename T, Alloc A> constexpr T *Str<T, A>::end() noexcept {
    return arr_ + len_;
}

template<typename T, Alloc A>
constexpr usz Str<T, A>::copy(Span<const T> src) noexcept {
    ensure(len_ + src.len());
    const usz n  = mem::copye(arr_ + len_, src.data(), cap_ - len_, src.len());
    len_        += n;
    arr_[len_]   = T{};
    return n;
}

template<typename T, Alloc A>
constexpr Span<const T> Str<T, A>::head(usz n) const noexcept {
    return { arr_, n };
}

template<typename T, Alloc A>
constexpr Span<T> Str<T, A>::head(usz n) noexcept {
    return { arr_, n };
}

template<typename T, Alloc A>
constexpr Span<const T> Str<T, A>::tail(usz n) const noexcept {
    return { arr_ + (len_ - n), n };
}

template<typename T, Alloc A>
constexpr Span<T> Str<T, A>::tail(usz n) noexcept {
    return { arr_ + (len_ - n), n };
}

template<typename T, Alloc A>
constexpr Span<const T> Str<T, A>::span(usz s, usz e) const noexcept {
    return { arr_ + s, e - s };
}

template<typename T, Alloc A>
constexpr Span<T> Str<T, A>::span(usz s, usz e) noexcept {
    return { arr_ + s, e - s };
}

template<typename T, Alloc A>
constexpr Span<const T> Str<T, A>::span(usz s) const noexcept {
    return { arr_ + s, len_ - s };
}

template<typename T, Alloc A>
constexpr Span<T> Str<T, A>::span(usz s) noexcept {
    return { arr_ + s, len_ - s };
}

template<typename T, Alloc A>
constexpr Span<const T> Str<T, A>::span() const noexcept {
    return *this;
}

template<typename T, Alloc A> constexpr Span<T> Str<T, A>::span() noexcept {
    return *this;
}

template<typename T, Alloc A> constexpr void Str<T, A>::cls() noexcept {
    mem::clse(arr_, len_ + 1);
    len_ = 0;
}

template<typename T, Alloc A> constexpr void Str<T, A>::free() noexcept {
    if (len_ != 0) return;

    alloc_.dealloc(arr_, cap_);
    arr_ = nullptr;
    cap_ = 0;
}

template<typename T, Alloc A> constexpr void Str<T, A>::res(usz cap) noexcept {
    if (cap <= cap_) return;

    T *arr = alloc_.alloc(cap);

    if (arr_ == nullptr) {
        arr_    = arr;
        cap_    = cap;
        arr_[0] = T{};
        return;
    }

    const usz n = mem::movee(arr, arr_, cap, len_ + 1);

    cls();
    free();

    arr_ = arr;
    len_ = n - 1;
    cap_ = cap;
}

template<typename T, Alloc A>
constexpr void Str<T, A>::ensure(usz len) noexcept {
    if (len + 1 <= cap_) return;

    const usz n = cap_ == 0 ? 8 : cap_ * 2;
    res(alg::max(n, len + 1));
}

template<typename T, Alloc A>
template<typename... U>
constexpr void Str<T, A>::emplace(U &&...args) noexcept {
    ensure(len_ + 1);
    mem::construct(arr_ + len_, fwd(args)...);
    arr_[++len_] = T{};
}

template<typename T, Alloc A>
constexpr void Str<T, A>::push(const T &val) noexcept {
    ensure(len_ + 1);
    mem::construct(arr_ + len_, val);
    arr_[++len_] = T{};
}

template<typename T, Alloc A> constexpr void Str<T, A>::push(T &&val) noexcept {
    ensure(len_ + 1);
    mem::construct(arr_ + len_, mv(val));
    arr_[++len_] = T{};
}

template<typename T, Alloc A> constexpr void Str<T, A>::pop() noexcept {
    if (len_ == 0) return;

    mem::destroy(arr_ + --len_);
    arr_[len_] = T{};
}

template<typename T, Alloc A>
constexpr usz Str<T, A>::find(Span<const T> sub) const noexcept {
    if (sub.len() > len_) return MAX_USZ;

    for (usz i = 0; i <= len_ - sub.len(); ++i)
        if (mem::cmpe(arr_ + i, sub.data(), sub.len())) return i;

    return MAX_USZ;
}

template<typename T, Alloc A>
constexpr usz Str<T, A>::find(const T &val) const noexcept {
    for (usz i = 0; i < len_; ++i)
        if (arr_[i] == val) return i;

    return MAX_USZ;
}

template<typename T, Alloc A>
constexpr bool Str<T, A>::prefix(Span<const T> pre) const noexcept {
    if (pre.len() > len_) return false;

    return mem::cmpe(arr_, pre.data(), pre.len());
}

template<typename T, Alloc A>
constexpr bool Str<T, A>::suffix(Span<const T> suf) const noexcept {
    if (suf.len() > len_) return false;

    return mem::cmpe(arr_ + (len_ - suf.len()), suf.data(), suf.len());
}

template<typename T, Alloc A>
constexpr bool Str<T, A>::contains(Span<const T> sub) const noexcept {
    if (sub.len() > len_) return false;

    for (usz i = 0; i <= len_ - sub.len(); ++i)
        if (mem::cmpe(arr_ + i, sub.data(), sub.len())) return true;

    return false;
}

template<typename T, Alloc A>
constexpr bool Str<T, A>::contains(const T &val) const noexcept {
    for (usz i = 0; i < len_; ++i)
        if (arr_[i] == val) return true;
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_STR_HPP_
