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

#ifndef SRR_IMPL_FREE_LIST_HPP_
#define SRR_IMPL_FREE_LIST_HPP_

inline namespace srr {
namespace impl {

struct Block {
    Block *next;
};

class FreeList {
public:
    [[nodiscard]] bool          empty() const noexcept;

    [[nodiscard]] Block *const &first() const noexcept;
    [[nodiscard]] Block       *&first() noexcept;

    [[nodiscard]] Block        *pop() noexcept;
    [[nodiscard]] Block        *pop(void *b) noexcept;

    void                        push(void *p) noexcept;

    void                        cls() noexcept;

private:
    Block *head_;
};

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_FREE_LIST_HPP_
