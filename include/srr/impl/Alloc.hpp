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

#ifndef SRR_IMPL_ALLOC_HPP_
#define SRR_IMPL_ALLOC_HPP_

#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename A>
concept Alloc = requires(A a, val_t<A> *ptr, usize n) {
    { a.alloc(n) } noexcept -> Same<val_t<A> *>;
    { a.dealloc(ptr, n) } noexcept -> Same<void>;
};

struct Block {
    Block *next;
};

class BlockList {
public:
    [[nodiscard]] bool   empty() const noexcept;
    [[nodiscard]] Block *pop() noexcept;
    [[nodiscard]] bool   tryrm(Block *b) noexcept;
    void                 push(Block *b) noexcept;

private:
    Block *head_;
};

class SysAlloc {
public:
    static void *alloc(usize n) noexcept;
    static void  dealloc(void *ptr, usize n) noexcept;

private:
    static constexpr usize N = 12;
    static BlockList       lists[N];
};

template<typename T> struct BaseAlloc {
    // NOLINTNEXTLINE(readability-identifier-naming)
    using val_t = T;

    T   *alloc(usize n) noexcept;
    void dealloc(T *ptr, usize n) noexcept;
};

static_assert(Alloc<BaseAlloc<byte>>);

// === impl ===

template<typename T> T *BaseAlloc<T>::alloc(usize n) noexcept {
    return static_cast<T *>(SysAlloc::alloc(n * sizeof(T)));
}

template<typename T> void BaseAlloc<T>::dealloc(T *ptr, usize n) noexcept {
    SysAlloc::dealloc(ptr, n * sizeof(T));
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_ALLOC_HPP_
