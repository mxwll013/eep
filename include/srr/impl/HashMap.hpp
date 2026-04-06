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

#ifndef SRR_IMPL_HASH_MAP_HPP_
#define SRR_IMPL_HASH_MAP_HPP_

#include "srr/impl/Alloc.hpp"
#include "srr/impl/Hasher.hpp"

#include "srr/alg.hpp"
#include "srr/ctr.hpp"
#include "srr/err.hpp"
#include "srr/mem.hpp"
#include "srr/traits.hpp"
#include "srr/types.hpp"

inline namespace srr {
namespace impl {

template<typename T, typename U>
concept Hashable = requires(Hasher<T> &h, const U &v) {
    { hash(h, v) } noexcept -> Same<void>;
};

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
class HashMap {
public:

    // NOLINTBEGIN(readability-identifier-naming)

    using hash_t  = T;
    using key_t   = K;
    using val_t   = V;
    using alloc_t = A;

    // NOLINTEND(readability-identifier-naming)

    constexpr HashMap() noexcept;
    constexpr HashMap(usz cap) noexcept;
    constexpr HashMap(const HashMap &other) noexcept;
    constexpr HashMap(HashMap &&other) noexcept;

    constexpr HashMap &operator=(const HashMap &other) noexcept;
    constexpr HashMap &operator=(HashMap &&other) noexcept;

    constexpr ~HashMap() noexcept;

    [[nodiscard]] constexpr usz      len() const noexcept;
    [[nodiscard]] constexpr usz      cap() const noexcept;
    [[nodiscard]] constexpr bool     empty() const noexcept;
    [[nodiscard]] constexpr bool     contains(const K &key) const noexcept;

    [[nodiscard]] constexpr const V *operator[](const K &key) const noexcept;
    [[nodiscard]] constexpr V       *operator[](const K &key) noexcept;
    [[nodiscard]] constexpr res<cref<V>> at(const K &key) const noexcept;
    [[nodiscard]] constexpr res<ref<V>>  at(const K &key) noexcept;

    constexpr void                       copy(const HashMap &other) noexcept;
    constexpr void                       steal(HashMap &&other) noexcept;

    constexpr void                       cls() noexcept;
    constexpr void                       free() noexcept;
    constexpr void                       res(usz cap) noexcept;
    constexpr void                       ensure(usz len) noexcept;

    template<typename... U>
    [[nodiscard]] constexpr err empl(const K &key, U &&...args) noexcept;
    template<typename... U>
    [[nodiscard]] constexpr err rempl(const K &key, U &&...args) noexcept;
    [[nodiscard]] constexpr err push(const K &key, const V &val) noexcept;
    [[nodiscard]] constexpr err push(const K &key, V &&val) noexcept;
    [[nodiscard]] constexpr err rpush(const K &key, const V &val) noexcept;
    [[nodiscard]] constexpr err rpush(const K &key, V &&val) noexcept;
    [[nodiscard]] constexpr err rm(const K &key) noexcept;

private:
    struct Entry {
        T    hash;
        usz  dist;
        bool occ;
    };

    [[nodiscard]] constexpr T   get(const K &key) const noexcept;
    [[nodiscard]] constexpr usz find(const K &key) const noexcept;
    [[nodiscard]] constexpr usz idx(const K &key) noexcept;

    constexpr void alloc(usz cap, Entry *&e, K *&k, V *&v, usz &c) noexcept;
    constexpr void dealloc(Entry *&e, K *&k, V *&v, usz &c) noexcept;

    static constexpr usz MAX_LF  = 75_usz;
    static constexpr usz MIN_CAP = 8_usz;
    static constexpr usz GRW_CAP = 2_usz;

    static constexpr usz E_SZ    = sizeof(Entry);
    static constexpr usz K_SZ    = sizeof(K);
    static constexpr usz V_SZ    = sizeof(V);
    static constexpr usz D_SZ    = E_SZ + K_SZ + V_SZ;

    A                    alloc_;

    Entry               *entr_ = nullptr;
    K                   *key_  = nullptr;
    V                   *val_  = nullptr;

    usz                  len_  = 0;
    usz                  cap_  = 0;
};

// === impl ===

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A>::HashMap() noexcept : alloc_{} {}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A>::HashMap(usz cap) noexcept : alloc_{} {
    alloc(cap, entr_, key_, val_, cap_);
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A>::HashMap(const HashMap &other) noexcept :
    alloc_{ other.alloc_ } {
    copy(other);
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A>::HashMap(HashMap &&other) noexcept :
    alloc_{ other.alloc_ } {
    steal(mv(other));
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A> &HashMap<T, K, V, A>::operator=(
    const HashMap &other) noexcept {
    if (this == &other) return *this;
    copy(other);
    return *this;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A> &HashMap<T, K, V, A>::operator=(
    HashMap &&other) noexcept {
    if (this == &other) return *this;
    steal(mv(other));
    return *this;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr HashMap<T, K, V, A>::~HashMap() noexcept {
    cls();
    dealloc(entr_, key_, val_, cap_);
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr usz HashMap<T, K, V, A>::len() const noexcept {
    return len_;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr usz HashMap<T, K, V, A>::cap() const noexcept {
    return cap_;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr bool HashMap<T, K, V, A>::empty() const noexcept {
    return len_ == 0;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr bool HashMap<T, K, V, A>::contains(const K &key) const noexcept {
    return find(key) != MAX_USZ;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr T HashMap<T, K, V, A>::get(const K &key) const noexcept {
    Hasher<T> h{};
    hash(h, key);
    return h.done();
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr usz HashMap<T, K, V, A>::find(const K &key) const noexcept {
    if (cap_ == 0) return MAX_USZ;

    const T h = get(key);
    usz     i = h & (cap_ - 1);
    usz     d = 0;

    while (true) {
        const Entry &e = entr_[i];

        if (!e.occ) return MAX_USZ;

        if (e.dist < d) return MAX_USZ;

        if (e.hash == h && key_[i] == key) return i;

        ++i;
        i &= (cap_ - 1);
        ++d;
    }
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr usz HashMap<T, K, V, A>::idx(const K &key) noexcept {
    T    h   = get(key);
    usz  i   = h & (cap_ - 1);
    usz  d   = 0;
    bool occ = false;

    usz  og  = MAX_USZ;

    while (true) {
        Entry &e = entr_[i];

        if (!e.occ) {
            e.hash = h;
            e.dist = d;
            e.occ  = occ;

            if (og == MAX_USZ) og = i;
            return og;
        }

        if (e.hash == h && key_[i] == key) return i;

        if (e.dist < d) {
            mem::swap(e.hash, h);
            mem::swap(e.dist, d);
            mem::swap(e.occ, occ);

            if (og == MAX_USZ) og = i;
        }

        ++i;
        i &= (cap_ - 1);
        ++d;
    }
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr const V *HashMap<T, K, V, A>::operator[](
    const K &key) const noexcept {
    const usz i = find(key);
    return i == MAX_USZ ? nullptr : &val_[i];
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr V *HashMap<T, K, V, A>::operator[](const K &key) noexcept {
    const usz i = find(key);
    return i == MAX_USZ ? nullptr : &val_[i];
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr res<cref<V>> HashMap<T, K, V, A>::at(const K &key) const noexcept {
    if (cap_ == 0) return err::EMPTY;
    const usz i = find(key);
    if (i == MAX_USZ) return err::NOT_FOUND;
    return val_[i];
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr res<ref<V>> HashMap<T, K, V, A>::at(const K &key) noexcept {
    if (cap_ == 0) return err::EMPTY;
    const usz i = find(key);
    if (i == MAX_USZ) return err::NOT_FOUND;
    return val_[i];
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::alloc(usz     cap,
                                          Entry *&e,
                                          K     *&k,
                                          V     *&v,
                                          usz    &c) noexcept {
    const usz eff = alg::ceil_pow2(cap);

    byte     *d   = alloc_.alloc(eff * D_SZ);

    e             = reinterpret_cast<Entry *>(d);
    k             = reinterpret_cast<K *>(d + (eff * E_SZ));
    v             = reinterpret_cast<V *>(d + (eff * (E_SZ + K_SZ)));
    c             = eff;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::dealloc(Entry *&e,
                                            K     *&k,
                                            V     *&v,
                                            usz    &c) noexcept {
    byte *d = reinterpret_cast<byte *>(e);

    alloc_.dealloc(d, c * D_SZ);
    e = nullptr;
    k = nullptr;
    v = nullptr;
    c = 0;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::copy(const HashMap &other) noexcept {
    if (this == &other) return;

    cls();

    if (cap_ != other.cap_) {
        free();
        alloc(other.cap_, entr_, key_, val_, cap_);
    }

    mem::copye(entr_, other.entr_, cap_, cap_);

    for (usz i = 0; i < cap_; ++i) {
        if (!entr_[i].occ) return;
        mem::construct(&key_[i], other.key_[i]);
        mem::construct(&val_[i], other.val_[i]);
    }

    len_ = other.len_;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::steal(HashMap &&other) noexcept {
    if (this == &other) return;

    cls();
    free();

    entr_       = other.entr_;
    key_        = other.key_;
    val_        = other.val_;
    len_        = other.len_;
    cap_        = other.cap_;

    other.entr_ = nullptr;
    other.key_  = nullptr;
    other.val_  = nullptr;
    other.len_  = 0;
    other.cap_  = 0;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::cls() noexcept {
    if (len_ == 0) return;

    mem::clse(entr_, len_);
    mem::clse(key_, len_);
    mem::clse(val_, len_);
    len_ = 0;
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::free() noexcept {
    if (len_ != 0) return;
    if (cap_ == 0) return;

    dealloc(entr_, key_, val_, cap_);
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::res(usz cap) noexcept {
    if (cap <= cap_) return;

    HashMap map{ cap };

    for (usz i = 0; i < cap_; ++i) {
        if (!entr_[i].occ) continue;

        (void) map.push(key_[i], val_[i]);
    }

    dealloc(entr_, key_, val_, cap_);

    steal(mv(map));
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr void HashMap<T, K, V, A>::ensure(usz len) noexcept {
    if (cap_ == 0) {
        res(alg::max(MIN_CAP, len));
        return;
    }

    if (len * 100 <= cap_ * MAX_LF) return;

    res(alg::max(cap_ * GRW_CAP, len));
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
template<typename... U>
constexpr err HashMap<T, K, V, A>::empl(const K &key, U &&...args) noexcept {
    ensure(len_ + 1);

    const usz i = idx(key);

    if (entr_[i].occ) return err::ALREADY_EXISTS;

    mem::construct(&val_[i], args...);
    mem::construct(&key_[i], key);
    entr_[i].occ = true;

    ++len_;
    return {};
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
template<typename... U>
constexpr err HashMap<T, K, V, A>::rempl(const K &key, U &&...args) noexcept {
    const usz i = find(key);

    if (i == MAX_USZ) return err::NOT_FOUND;

    val_[i] = V{ args... };
    return {};
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr err HashMap<T, K, V, A>::push(const K &key, const V &val) noexcept {
    return empl(key, val);
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr err HashMap<T, K, V, A>::push(const K &key, V &&val) noexcept {
    return empl(key, mv(val));
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr err HashMap<T, K, V, A>::rpush(const K &key, const V &val) noexcept {
    return rempl(key, val);
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr err HashMap<T, K, V, A>::rpush(const K &key, V &&val) noexcept {
    return rempl(key, mv(val));
}

template<typename T, typename K, typename V, Alloc A>
    requires Hashable<T, K>
constexpr err HashMap<T, K, V, A>::rm(const K &key) noexcept {
    usz i = find(key);

    if (i == MAX_USZ) return err::NOT_FOUND;

    usz n = (i + 1) & (cap_ - 1);

    while (entr_[n].occ && entr_[n].dist > 0) {
        entr_[i] = entr_[n];
        entr_[i].dist--;

        key_[i] = mv(key_[n]);
        val_[i] = mv(val_[n]);

        i       = n;
        ++n;
        n &= (cap_ - 1);
    }

    entr_[i].occ = false;

    --len_;
    return {};
}

} // namespace impl
} // namespace srr

#endif // SRR_IMPL_HASH_MAP_HPP_
