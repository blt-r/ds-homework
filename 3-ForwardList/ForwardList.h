#pragma once
#include <algorithm>
#include <optional>
#include <ostream>
#include <utility>

template <typename T>
class ForwardList {
    struct NodeHeader {
        NodeHeader* next;
        NodeHeader(NodeHeader* next);
    };
    struct Node : NodeHeader {
        T data;
        template <typename... Args>
            requires requires(Args... args) { T(std::forward<Args>(args)...); }
        Node(NodeHeader* next, Args&&... args);
    };

    NodeHeader root = NodeHeader(nullptr);

   public:
    ForwardList();
    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    explicit ForwardList(std::size_t n, Args&&... args);
    ForwardList(std::size_t n, const T& value);

    template <std::input_iterator It, std::sentinel_for<It> Sn>
        requires std::constructible_from<std::iter_value_t<It>, T>
    ForwardList(It begin, Sn end);
    ForwardList(std::initializer_list<T> list);

    ForwardList(const ForwardList& other);
    auto operator=(const ForwardList& other) -> ForwardList&;
    ~ForwardList();

    class iterator {
        friend class ForwardList<T>;  // good oop
        NodeHeader* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        iterator(NodeHeader* node = nullptr);
        auto operator==(const iterator& other) const -> bool;
        auto operator++() -> iterator&;    // Prefix
        auto operator++(int) -> iterator;  // Postfix
        auto operator*() const -> T&;
        auto operator->() const -> T*;
    };

    static_assert(std::forward_iterator<iterator>);
    static_assert(std::output_iterator<iterator, T>);

    class const_iterator {
        const NodeHeader* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;

        const_iterator(NodeHeader* node = nullptr);
        const_iterator(const iterator& non_const);
        auto operator==(const const_iterator& other) const -> bool;
        auto operator++() -> const_iterator&;    // Prefix
        auto operator++(int) -> const_iterator;  // Postfix
        auto operator*() const -> const T&;
        auto operator->() const -> const T*;
    };

    static_assert(std::forward_iterator<const_iterator>);

    auto before_begin() -> iterator;
    auto begin() -> iterator;
    auto end() -> iterator;
    auto cbefore_begin() const -> const_iterator;
    auto cbegin() const -> const_iterator;
    auto cend() const -> const_iterator;
    auto before_begin() const -> const_iterator;
    auto begin() const -> const_iterator;
    auto end() const -> const_iterator;

    auto front() -> T&;
    auto front() const -> const T&;
    auto empty() -> bool;
    auto clear() -> void;
    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    auto emplace_after(iterator it, Args&&... args) -> void;
    auto insert_after(iterator it, const T& value) -> void;
    auto insert_after(iterator it, T&& value) -> void;
    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    auto emplace_front(Args&&... args) -> void;
    auto push_front(const T& value) -> void;
    auto push_front(T&& value) -> void;
    auto erase_after(iterator it) -> void;
    auto pop_front() -> void;
    auto operator==(const ForwardList& other) const -> bool;
};

template <typename T>
ForwardList<T>::NodeHeader::NodeHeader(NodeHeader* next) : next(next) {}

template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
ForwardList<T>::Node::Node(NodeHeader* next, Args&&... args)
    : NodeHeader(next), data(std::forward<Args>(args)...) {}

template <typename T>
ForwardList<T>::ForwardList() {}

template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
ForwardList<T>::ForwardList(std::size_t n, Args&&... args) {
    NodeHeader* tail = &root;

    for (std::size_t i = 0; i < n; ++i) {
        tail->next = new Node(nullptr, std::forward<Args>(args)...);
        tail = tail->next;
    }
}
template <typename T>
template <std::input_iterator It, std::sentinel_for<It> Sn>
    requires std::constructible_from<std::iter_value_t<It>, T>
ForwardList<T>::ForwardList(It begin, Sn end) {
    NodeHeader* tail = &root;

    while (begin != end) {
        tail->next = new Node(nullptr, *begin);
        tail = tail->next;
        ++begin;
    }
}
template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> list)
    : ForwardList(list.begin(), list.end()) {}

// Rule of Five (-2)
template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other)
    : ForwardList(other.cbegin(), other.cend()) {}

template <typename T>
auto ForwardList<T>::operator=(const ForwardList& other) -> ForwardList<T>& {
    NodeHeader* tail = &root;
    const NodeHeader* their_tail = &other.root;

    while (their_tail->next != nullptr) {
        if (tail->next != nullptr) {
            static_cast<Node*>(tail->next)->data =
                static_cast<Node*>(their_tail->next)->data;
        } else {
            tail->next =
                new Node(nullptr, static_cast<Node*>(their_tail->next)->data);
        }

        tail = tail->next;
        their_tail = their_tail->next;
    }

    NodeHeader* after_tail = tail->next;
    tail->next = nullptr;

    while (after_tail != nullptr) {
        NodeHeader* next = after_tail->next;

        delete static_cast<Node*>(after_tail);

        after_tail = next;
    }

    return *this;
}

template <typename T>
ForwardList<T>::~ForwardList() {
    NodeHeader* tail = root.next;

    while (tail != nullptr) {
        NodeHeader* next = tail->next;

        delete static_cast<Node*>(tail);

        tail = next;
    }
}

template <typename T>
ForwardList<T>::iterator::iterator(NodeHeader* node) : node(node) {}

template <typename T>
auto ForwardList<T>::iterator::operator==(const iterator& other) const
    -> bool = default;

// Prefix
template <typename T>
auto ForwardList<T>::iterator::operator++() -> iterator& {
    node = node->next;
    return *this;
}

// Postfix
template <typename T>
auto ForwardList<T>::iterator::operator++(int) -> iterator {
    auto old = *this;
    ++*this;
    return old;
}
template <typename T>
auto ForwardList<T>::iterator::operator*() const -> T& {
    return static_cast<Node*>(node)->data;
}
template <typename T>
auto ForwardList<T>::iterator::operator->() const -> T* {
    return &static_cast<Node*>(node)->data;
}

template <typename T>
ForwardList<T>::const_iterator::const_iterator(NodeHeader* node) : node(node) {}

template <typename T>
ForwardList<T>::const_iterator::const_iterator(const iterator& non_const)
    : node(non_const.node) {}

template <typename T>
auto ForwardList<T>::const_iterator::operator==(
    const const_iterator& other) const -> bool = default;

// Prefix
template <typename T>
auto ForwardList<T>::const_iterator::operator++() -> const_iterator& {
    node = node->next;
    return *this;
}
// Postfix
template <typename T>
auto ForwardList<T>::const_iterator::operator++(int) -> const_iterator {
    auto old = *this;
    ++*this;
    return old;
}
template <typename T>
auto ForwardList<T>::const_iterator::operator*() const -> const T& {
    return static_cast<const Node*>(node)->data;
}
template <typename T>
auto ForwardList<T>::const_iterator::operator->() const -> const T* {
    return &static_cast<const Node*>(node)->data;
}
template <typename T>
auto ForwardList<T>::before_begin() -> iterator {
    return iterator(&root);
}
template <typename T>
auto ForwardList<T>::begin() -> iterator {
    return iterator(root.next);
}
template <typename T>
auto ForwardList<T>::end() -> iterator {
    return iterator();
}
template <typename T>
auto ForwardList<T>::cbefore_begin() const -> const_iterator {
    return const_iterator(&root);
}
template <typename T>
auto ForwardList<T>::cbegin() const -> const_iterator {
    return const_iterator(root.next);
}
template <typename T>
auto ForwardList<T>::cend() const -> const_iterator {
    return const_iterator();
}
template <typename T>
auto ForwardList<T>::before_begin() const -> const_iterator {
    return cbefore_begin();
}
template <typename T>
auto ForwardList<T>::begin() const -> const_iterator {
    return cbegin();
}
template <typename T>
auto ForwardList<T>::end() const -> const_iterator {
    return cend();
}

template <typename T>
auto ForwardList<T>::front() -> T& {
    return static_cast<Node*>(root.next)->data;
}
template <typename T>
auto ForwardList<T>::front() const -> const T& {
    return static_cast<Node*>(root.next)->data;
}
template <typename T>
auto ForwardList<T>::empty() -> bool {
    return root.next == nullptr;
}
template <typename T>
auto ForwardList<T>::clear() -> void {
    this->~ForwardList();
    root.next = nullptr;
}
template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
auto ForwardList<T>::emplace_after(iterator it, Args&&... args) -> void {
    NodeHeader* new_node = new Node(it.node->next, std::forward<Args>(args)...);
    it.node->next = new_node;
}
template <typename T>
auto ForwardList<T>::insert_after(iterator it, const T& value) -> void {
    emplace_after(it, value);
}
template <typename T>
auto ForwardList<T>::insert_after(iterator it, T&& value) -> void {
    emplace_after(it, std::move(value));
}
template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
auto ForwardList<T>::emplace_front(Args&&... args) -> void {
    emplace_after(before_begin(), std::forward<Args>(args)...);
}
template <typename T>
auto ForwardList<T>::push_front(const T& value) -> void {
    emplace_front(value);
}
template <typename T>
auto ForwardList<T>::push_front(T&& value) -> void {
    emplace_front(std::move(value));
}
template <typename T>
auto ForwardList<T>::erase_after(iterator it) -> void {
    if (it.node == nullptr)
        return;

    if (it.node->next != nullptr) {
        NodeHeader* new_next = it.node->next->next;

        delete static_cast<Node*>(it.node->next);

        it.node->next = new_next;
    }
}
template <typename T>
auto ForwardList<T>::pop_front() -> void {
    erase_after(before_begin());
}

template <typename T>
auto ForwardList<T>::operator==(const ForwardList& other) const -> bool {
    return std::ranges::equal(begin(), end(), other.begin(), other.end());
}

template <typename T>
auto operator<<(std::ostream& os, const ForwardList<T>& list) -> std::ostream& {
    auto begin = list.begin();
    auto end = list.end();

    os << '[';
    if (begin != end) {
        os << *begin;
        ++begin;
    }

    while (begin != end) {
        os << " -> " << *begin;
        ++begin;
    }
    os << ']';
    return os;
}
