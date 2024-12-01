#pragma once

#include <bit>
#include <memory>
#include <ostream>

template <typename T, typename A = std::allocator<T>>
class Vector {
  private:
    using AllocT = std::allocator_traits<A>;

  public:
    using sz_t = AllocT::size_type;

  private:
    T* ptr;
    sz_t len;
    sz_t cap;
    [[no_unique_address]]
    A alloc;

    static constexpr sz_t INITIAL_CAPACITY = 8;

    auto resize(sz_t new_cap) -> void;

  public:
    Vector();
    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    explicit Vector(sz_t n, const Args&... args);
    Vector(std::initializer_list<T> list);

    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    auto operator=(const Vector& other) -> Vector&;
    auto operator=(Vector&& other) noexcept -> Vector&;
    ~Vector();

    auto data() const -> T*;
    auto size() const -> sz_t;
    auto capacity() const -> sz_t;
    auto push_back(const T& value) -> void;
    auto push_back(T&& value) -> void;
    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    auto emplace_back(Args&&... args) -> void;
    auto pop_back() -> void;
    auto clear() -> void;
    auto reserve(sz_t new_cap) -> void;
    auto shrink_to_fit() -> void;
    auto empty() const -> bool;
    auto front() -> T&;
    auto front() const -> const T&;
    auto back() -> T&;
    auto back() const -> const T&;
    auto swap(Vector& other) noexcept -> void;
    auto at(sz_t n) -> T&;
    auto at(sz_t n) const -> const T&;

    auto operator[](sz_t n) -> T&;
    auto operator[](sz_t n) const -> const T&;
    auto operator==(const Vector& other) const -> bool;
};

template <typename T, typename A>
auto Vector<T, A>::resize(sz_t new_cap) -> void {
    if (new_cap == cap)
        return;

    T* new_ptr = AllocT::allocate(alloc, new_cap);

    for (sz_t i = 0; i < len; i++) {
        AllocT::construct(alloc, &new_ptr[i], std::move(ptr[i]));
        AllocT::destroy(alloc, &ptr[i]);
    }

    AllocT::deallocate(alloc, ptr, cap);

    ptr = new_ptr;
    cap = new_cap;
}

template <typename T, typename A>
auto Vector<T, A>::data() const -> T* {
    // data() should never return null pointer
    return ptr ? ptr : std::bit_cast<T*>(alignof(T));
}
template <typename T, typename A>
auto Vector<T, A>::size() const -> sz_t {
    return len;
}
template <typename T, typename A>
auto Vector<T, A>::capacity() const -> sz_t {
    return cap;
}
template <typename T, typename A>
auto Vector<T, A>::push_back(const T& value) -> void {
    if (len == cap) {
        resize(cap ? cap * 2 : INITIAL_CAPACITY);
    }

    AllocT::construct(alloc, &ptr[len], value);
    len += 1;
}
template <typename T, typename A>
auto Vector<T, A>::push_back(T&& value) -> void {
    if (len == cap) {
        resize(cap ? cap * 2 : INITIAL_CAPACITY);
    }

    AllocT::construct(alloc, &ptr[len], std::move(value));
    len += 1;
}

template <typename T, typename A>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
auto Vector<T, A>::emplace_back(Args&&... args) -> void {
    if (len == cap) {
        resize(cap ? cap * 2 : INITIAL_CAPACITY);
    }

    AllocT::construct(alloc, &ptr[len], std::forward<Args>(args)...);
    len += 1;
}
template <typename T, typename A>
auto Vector<T, A>::pop_back() -> void {
    if (len == 0)
        return;
    len -= 1;
    AllocT::destroy(alloc, &ptr[len]);
}
template <typename T, typename A>
auto Vector<T, A>::clear() -> void {
    for (T* p = ptr; p < ptr + len; ++p) {
        AllocT::destroy(alloc, p);
    }
    len = 0;
}
template <typename T, typename A>
auto Vector<T, A>::reserve(sz_t new_cap) -> void {
    if (new_cap > cap)
        resize(new_cap);
}
template <typename T, typename A>
auto Vector<T, A>::shrink_to_fit() -> void {
    resize(len);
}
template <typename T, typename A>
auto Vector<T, A>::empty() const -> bool {
    return len == 0;
};
template <typename T, typename A>
auto Vector<T, A>::front() -> T& {
    return (*this)[0];
};
template <typename T, typename A>
auto Vector<T, A>::front() const -> const T& {
    return (*this)[0];
};
template <typename T, typename A>
auto Vector<T, A>::back() -> T& {
    return (*this)[len - 1];
};
template <typename T, typename A>
auto Vector<T, A>::back() const -> const T& {
    return (*this)[len - 1];
};
template <typename T, typename A>
auto Vector<T, A>::swap(Vector& other) noexcept -> void {
    std::swap(ptr, other.ptr);
    std::swap(len, other.len);
    std::swap(cap, other.cap);

    if (AllocT::propagate_on_container_swap::value) {
        std::swap(alloc, other.alloc);
    }
}
template <typename T, typename A>
auto Vector<T, A>::at(sz_t n) -> T& {
    if (n < 0 || n >= len)
        throw std::out_of_range("index is out of range");

    return (*this)[n];
}
template <typename T, typename A>
auto Vector<T, A>::at(sz_t n) const -> const T& {
    if (n < 0 || n >= len)
        throw std::out_of_range("index is out of range");

    return (*this)[n];
}

// Constructors
template <typename T, typename A>
Vector<T, A>::Vector() : ptr(nullptr), len(0), cap(0), alloc() {}

template <typename T, typename A>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
Vector<T, A>::Vector(sz_t n, const Args&... args) : len(n), cap(n), alloc() {
    ptr = AllocT::allocate(alloc, cap);
    for (T* p = ptr; p < ptr + len; ++p) {
        AllocT::construct(alloc, p, args...);
    }
}
template <typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> list) {
    cap = list.size();
    len = list.size();
    ptr = AllocT::allocate(alloc, cap);

    auto p = ptr;
    auto l = list.begin();
    for (; p < ptr + len; ++p, ++l) {
        AllocT::construct(alloc, p, *l);
    }
}

// Rule of five
template <typename T, typename A>
Vector<T, A>::Vector(const Vector& other) {
    cap = other.cap;
    len = other.len;

    ptr = AllocT::allocate(alloc, cap);

    for (sz_t i = 0; i < len; i++) {
        AllocT::construct(alloc, &ptr[i], other[i]);
    }
}
template <typename T, typename A>
Vector<T, A>::Vector(Vector&& other) noexcept {
    cap = other.cap;
    len = other.len;
    ptr = other.ptr;

    other.cap = 0;
    other.len = 0;
    other.ptr = nullptr;
}
template <typename T, typename A>
auto Vector<T, A>::operator=(const Vector& other) -> Vector<T, A>& {
    if (&other == this)
        return *this;

    this->~Vector();

    cap = other.cap;
    len = other.len;

    ptr = AllocT::allocate(alloc, cap);

    for (sz_t i = 0; i < len; i++) {
        AllocT::construct(alloc, &ptr[i], other[i]);
    }

    return *this;
}
template <typename T, typename A>
auto Vector<T, A>::operator=(Vector&& other) noexcept -> Vector<T, A>& {
    if (&other == this)
        return *this;

    this->~Vector();

    cap = other.cap;
    len = other.len;
    ptr = other.ptr;

    other.cap = 0;
    other.len = 0;
    other.ptr = nullptr;

    return *this;
}
template <typename T, typename A>
Vector<T, A>::~Vector() {
    clear();
    AllocT::deallocate(alloc, ptr, cap);
}

// Operators
template <typename T, typename A>
auto Vector<T, A>::operator[](sz_t n) -> T& {
    return ptr[n];
}
template <typename T, typename A>
auto Vector<T, A>::operator[](sz_t n) const -> const T& {
    return ptr[n];
}
template <typename T, typename A>
auto Vector<T, A>::operator==(const Vector& other) const -> bool {
    return std::equal(ptr, ptr + len, other.ptr, other.ptr + other.len);
}

template <typename T, typename A>
auto operator<<(std::ostream& os, const Vector<T, A>& vec) -> std::ostream& {
    os << '[';
    if (vec.size() > 0) {
        os << vec[0];
    }
    for (typename Vector<T, A>::sz_t i = 1; i < vec.size(); ++i) {
        os << ", " << vec[i];
    }
    os << ']';

    return os;
}
