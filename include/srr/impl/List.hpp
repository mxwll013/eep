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

#ifndef SRR_IMPL_LIST_HPP_
#define SRR_IMPL_LIST_HPP_

#include "srr/impl/Alloc.hpp"
#include "srr/impl/Span.hpp"

#include "srr/mem.hpp"
#include "srr/types.hpp"

#include <cstdio>

inline namespace srr {
namespace impl {

template<typename T, Alloc A> class List {
public:
    // NOLINTBEGIN(readability-identifier-naming)
    using val_t = T;
    using alloc_t = A;
    // NOLINTEND(readability-identifier-naming)

    constexpr List() noexcept;
    constexpr List(usize cap) noexcept;
    constexpr List(const List &other) noexcept;
    constexpr List(List &&other) noexcept;

    constexpr List &operator=(const List &other) noexcept;
    constexpr List &operator=(List &&other) noexcept;

    ~List() noexcept;

    constexpr                        operator Span<T>() noexcept;
    constexpr                        operator Span<const T>() const noexcept;

    [[nodiscard]] constexpr usize    len() const noexcept;
    [[nodiscard]] constexpr usize    cap() const noexcept;
    [[nodiscard]] constexpr bool     empty() const noexcept;

    [[nodiscard]] constexpr const T &operator[](usize i) const noexcept;
    [[nodiscard]] constexpr T       &operator[](usize i) noexcept;
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

    [[nodiscard]] constexpr usize    copy(Span<const T> src) noexcept;

    [[nodiscard]] constexpr Span<const T> head(usize n) const noexcept;
    [[nodiscard]] constexpr Span<T>       head(usize n) noexcept;
    [[nodiscard]] constexpr Span<const T> tail(usize n) const noexcept;
    [[nodiscard]] constexpr Span<T>       tail(usize n) noexcept;
    [[nodiscard]] constexpr Span<const T> span(usize s, usize e) const noexcept;
    [[nodiscard]] constexpr Span<T>       span(usize s, usize e) noexcept;
    [[nodiscard]] constexpr Span<const T> span(usize s) const noexcept;
    [[nodiscard]] constexpr Span<T>       span(usize s) noexcept;
    [[nodiscard]] constexpr Span<const T> span() const noexcept;
    [[nodiscard]] constexpr Span<T>       span() noexcept;

    constexpr void                        cls() noexcept;
    constexpr void                        free() noexcept;
    constexpr void                        res(usize cap) noexcept;
    constexpr void                        ensure(usize len) noexcept;

    template<typename... U> constexpr void emplace(U &&...args) noexcept;
    constexpr void                         push(const T &val) noexcept;
    constexpr void                         push(T &&val) noexcept;
    constexpr void                         pop() noexcept;

private:
    A     alloc_;
    T    *arr_;
    usize len_;
    usize cap_;
};

// === impl ===

template<typename T, Alloc A>
constexpr List<T, A>::List() noexcept :
    alloc_{},
    arr_{ nullptr },
    len_{ 0 },
    cap_{ 0 } {}

template<typename T, Alloc A>
constexpr List<T, A>::List(usize cap) noexcept :
    alloc_{},
    arr_{ alloc_.alloc(cap) },
    len_{ 0 },
    cap_{ cap } {}

template<typename T, Alloc A>
constexpr List<T, A>::List(const List &other) noexcept :
    alloc_{ other.alloc_ },
    arr_{ alloc_.alloc(other.cap_) },
    len_{ other.len_ },
    cap_{ other.cap_ } {
    copy(other);
}

template<typename T, Alloc A>
constexpr List<T, A>::List(List &&other) noexcept :
    alloc_{ other.alloc_ },
    arr_{ other.arr_ },
    len_{ other.len_ },
    cap_{ other.cap_ } {
    other.arr_ = nullptr;
    other.len_ = 0;
    other.cap_ = 0;
}

template<typename T, Alloc A>
constexpr List<T, A> &List<T, A>::operator=(const List &other) noexcept {
    if (this == &other) return *this;

    cls();
    free();

    alloc_ = other.alloc_;
    arr_   = alloc_.alloc(other.cap_);
    len_   = other.len_;
    cap_   = other.cap_;

    copy(other);
    return *this;
}

template<typename T, Alloc A>
constexpr List<T, A> &List<T, A>::operator=(List &&other) noexcept {
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

template<typename T, Alloc A> List<T, A>::~List() noexcept {
    cls();
    free();
}

template<typename T, Alloc A>
constexpr List<T, A>::operator Span<T>() noexcept {
    return { arr_, len_ };
}

template<typename T, Alloc A>
constexpr List<T, A>::operator Span<const T>() const noexcept {
    return { arr_, len_ };
}

template<typename T, Alloc A> constexpr usize List<T, A>::len() const noexcept {
    return len_;
}

template<typename T, Alloc A> constexpr usize List<T, A>::cap() const noexcept {
    return cap_;
}

template<typename T, Alloc A>
constexpr bool List<T, A>::empty() const noexcept {
    return len_ == 0;
}

template<typename T, Alloc A>
constexpr const T &List<T, A>::operator[](usize i) const noexcept {
    return arr_[i];
}

template<typename T, Alloc A>
constexpr T &List<T, A>::operator[](usize i) noexcept {
    return arr_[i];
}

template<typename T, Alloc A>
constexpr const T &List<T, A>::first() const noexcept {
    return arr_[0];
}

template<typename T, Alloc A> constexpr T &List<T, A>::first() noexcept {
    return arr_[0];
}

template<typename T, Alloc A>
constexpr const T &List<T, A>::last() const noexcept {
    return arr_[len_ - 1];
}

template<typename T, Alloc A> constexpr T &List<T, A>::last() noexcept {
    return arr_[len_ - 1];
}

template<typename T, Alloc A>
constexpr const T *List<T, A>::data() const noexcept {
    return arr_;
}

template<typename T, Alloc A> constexpr T *List<T, A>::data() noexcept {
    return arr_;
}

template<typename T, Alloc A>
constexpr const T *List<T, A>::begin() const noexcept {
    return arr_;
}

template<typename T, Alloc A> constexpr T *List<T, A>::begin() noexcept {
    return arr_;
}

template<typename T, Alloc A>
constexpr const T *List<T, A>::end() const noexcept {
    return arr_ + len_;
}

template<typename T, Alloc A> constexpr T *List<T, A>::end() noexcept {
    return arr_ + len_;
}

template<typename T, Alloc A>
constexpr usize List<T, A>::copy(Span<const T> src) noexcept {
    const usize n = mem::copye(arr_ + len_, src.data(), cap_ - len_, src.len());
    len_ += n;
    return n;
}

template<typename T, Alloc A>
constexpr Span<const T> List<T, A>::head(usize n) const noexcept {
    return { arr_, n };
}

template<typename T, Alloc A>
constexpr Span<T> List<T, A>::head(usize n) noexcept {
    return { arr_, n };
}

template<typename T, Alloc A>
constexpr Span<const T> List<T, A>::tail(usize n) const noexcept {
    return { arr_ + (len_ - n), n };
}

template<typename T, Alloc A>
constexpr Span<T> List<T, A>::tail(usize n) noexcept {
    return { arr_ + (len_ - n), n };
}

template<typename T, Alloc A>
constexpr Span<const T> List<T, A>::span(usize s, usize e) const noexcept {
    return { arr_ + s, e - s };
}

template<typename T, Alloc A>
constexpr Span<T> List<T, A>::span(usize s, usize e) noexcept {
    return { arr_ + s, e - s };
}

template<typename T, Alloc A>
constexpr Span<const T> List<T, A>::span(usize s) const noexcept {
    return { arr_ + s, len_ - s };
}

template<typename T, Alloc A>
constexpr Span<T> List<T, A>::span(usize s) noexcept {
    return { arr_ + s, len_ - s };
}

template<typename T, Alloc A>
constexpr Span<const T> List<T, A>::span() const noexcept {
    return *this;
}

template<typename T, Alloc A> constexpr Span<T> List<T, A>::span() noexcept {
    return *this;
}

template<typename T, Alloc A> constexpr void List<T, A>::cls() noexcept {
    mem::clse(arr_, len_);
    len_ = 0;
}

template<typename T, Alloc A> constexpr void List<T, A>::free() noexcept {
    if (len_ != 0) return;

    alloc_.dealloc(arr_, cap_);
    arr_ = nullptr;
    cap_ = 0;
}

template<typename T, Alloc A>
constexpr void List<T, A>::res(usize cap) noexcept {
    if (cap <= cap_) return;

    T          *arr = alloc_.alloc(cap);

    const usize n   = mem::movee(arr, arr_, cap, len_);

    cls();
    free();

    arr_ = arr;
    len_ = n;
    cap_ = cap;
}

template<typename T, Alloc A>
constexpr void List<T, A>::ensure(usize len) noexcept {
    if (len <= cap_) return;
    res(cap_ == 0 ? 1 : cap_ * 2);
}

template<typename T, Alloc A>
template<typename... U>
constexpr void List<T, A>::emplace(U &&...args) noexcept {
    ensure(len_ + 1);
    mem::construct(arr_ + len_, fwd(args)...);
    len_++;
}

template<typename T, Alloc A>
constexpr void List<T, A>::push(const T &val) noexcept {
    ensure(len_ + 1);
    mem::construct(arr_ + len_, val);
    len_++;
}

template<typename T, Alloc A>
constexpr void List<T, A>::push(T &&val) noexcept {
    ensure(len_ + 1);
    mem::construct(arr_ + len_, mv(val));
    len_++;
}

template<typename T, Alloc A> constexpr void List<T, A>::pop() noexcept {
    if (len_ == 0) return;

    len_--;
    mem::destroy(arr_ + len_);
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_LIST_HPP_
