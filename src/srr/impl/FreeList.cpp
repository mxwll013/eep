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

#include "srr/impl/FreeList.hpp"

inline namespace srr {
namespace impl {

bool   FreeList::empty() const noexcept { return head_ == nullptr; }

Block *FreeList::pop() noexcept {
    // NOLINTNEXTLINE(misc-const-correctness)
    Block *b = head_;
    if (b != nullptr) head_ = head_->next;
    return b;
}

Block *FreeList::pop(void *b) noexcept {
    if (head_ == b) {
        head_ = head_->next;
        return static_cast<Block *>(b);
    }

    for (Block *p = head_; p != nullptr; p = p->next) {
        if (p->next == b) {
            p->next = p->next->next;
            return static_cast<Block *>(b);
        }
    }

    return nullptr;
}

void FreeList::push(void *p) noexcept {
    Block *b = static_cast<Block *>(p);
    b->next  = head_;
    head_    = b;
}

void FreeList::cls() noexcept { head_ = nullptr; }

} // namespace impl
} // namespace srr
