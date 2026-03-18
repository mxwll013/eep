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

#include "srr/impl/Alloc.hpp"

#include "srr/alg.hpp"
#include "srr/sys.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

namespace {

usz index(usz n) noexcept { return alg::ceil_log2(alg::max(n, sizeof(Block))); }

Block *split(Block *b, usz i) noexcept {
    return reinterpret_cast<Block *>(reinterpret_cast<byte *>(b) +
                                     (1_usz << i));
}

Block *buddy(Block *b, usz n) noexcept {
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    return reinterpret_cast<Block *>(reinterpret_cast<usz>(b) ^ n);
}

} // namespace

BlockList SysAlloc::lists[SysAlloc::N] = {};

bool      BlockList::empty() const noexcept { return head_ == nullptr; }

Block    *BlockList::pop() noexcept {
    Block *b = head_;
    if (b != nullptr) head_ = head_->next;
    return b;
}

bool BlockList::tryrm(Block *b) noexcept {
    if (head_ == b) {
        head_ = head_->next;
        return true;
    }

    for (Block *p = head_; p != nullptr; p = p->next) {
        if (p->next == b) {
            p->next = b->next;
            return true;
        }
    }

    return false;
}

void BlockList::push(Block *b) noexcept {
    b->next = head_;
    head_   = b;
}

void *SysAlloc::alloc(usz n) noexcept {
    if (n == 0) return nullptr;
    if (n > sys::PAGE_SIZE) return sys::mmap(n);

    const usz k = index(n);
    n           = 1_usz << k;

    usz i       = k;
    while (i < N && lists[i].empty()) ++i;

    Block *p = nullptr;

    if (i == N) {
        --i;
        p       = static_cast<Block *>(sys::mmap(1_usz << N));
        p->next = nullptr;
    } else {
        p = lists[i].pop();
    }

    while (i > k) {
        --i;
        Block *q = split(p, i);
        lists[i].push(q);
    }

    return p;
}

void SysAlloc::dealloc(void *ptr, usz n) noexcept {
    if (ptr == nullptr) return;
    if (n > sys::PAGE_SIZE) {
        sys::munmap(ptr, n);
        return;
    }

    usz    k = index(n);
    Block *b = static_cast<Block *>(ptr);

    while (k < N - 1) {
        n        = 1_usz << k;
        Block *q = buddy(b, n);

        if (!lists[k].tryrm(q)) break;

        b = alg::min(b, q);
        ++k;
    }

    lists[k].push(b);
}

} // namespace impl
} // namespace srr
