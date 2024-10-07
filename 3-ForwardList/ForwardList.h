#pragma once
#include <algorithm>
#include <optional>
#include <ostream>
#include <utility>

struct Empty {};
static constexpr Empty empty_val{};

template <typename T>
class ForwardList {
    struct Node {
        Node* next = nullptr;
        union {
            T data;
            Empty empty;
        };

        template <typename... Args>
        Node(std::in_place_t, Args&&... args);
        Node(Empty);

        auto destroy_data() -> void;
        ~Node();  // Does nothing. Use destroy_data to destroy data.
    };

    Node root = Node(empty_val);

   public:
    ForwardList();
    template <typename... Args>
    explicit ForwardList(std::size_t n, Args&&... args);
    ForwardList(std::size_t n, const T& value);

    template <std::input_iterator It, std::sentinel_for<It> Sn>
        requires std::is_same<T, std::iter_value_t<It>>::value
    ForwardList(It begin, Sn end);
    ForwardList(std::initializer_list<T> list);

    ForwardList(const ForwardList& other);
    auto operator=(const ForwardList& other) -> ForwardList&;
    ~ForwardList();

    class iterator {
        friend class ForwardList<T>;  // good oop
        Node* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        iterator(Node* node = nullptr);
        auto operator==(const iterator& other) const -> bool;
        auto operator++() -> iterator&;    // Prefix
        auto operator++(int) -> iterator;  // postfix
        auto operator*() const -> T&;
        auto operator->() const -> T*;
    };

    static_assert(std::forward_iterator<iterator>);
    static_assert(std::output_iterator<iterator, T>);

    class const_iterator {
        const Node* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;

        const_iterator(Node* node = nullptr);
        const_iterator(const iterator& non_const);
        auto operator==(const const_iterator& other) const -> bool;
        auto operator++() -> const_iterator&;    // Prefix
        auto operator++(int) -> const_iterator;  // postfix
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
    auto emplace_after(iterator it, Args&&... args) -> void;
    auto insert_after(iterator it, const T& value) -> void;
    auto insert_after(iterator it, T&& value) -> void;
    template <typename... Args>
    auto emplace_front(Args&&... args) -> void;
    auto push_front(const T& value) -> void;
    auto push_front(T&& value) -> void;
    auto erase_after(iterator it) -> void;
    auto pop_front() -> void;
    auto operator==(const ForwardList& other) const -> bool;
};

template <typename T>
template <typename... Args>
ForwardList<T>::Node::Node(std::in_place_t, Args&&... args)
    : data(std::forward<Args>(args)...) {}

template <typename T>
ForwardList<T>::Node::Node(Empty) : empty() {}

template <typename T>
auto ForwardList<T>::Node::destroy_data() -> void {
    std::destroy_at(&data);
}

template <typename T>
ForwardList<T>::Node::~Node() {}

template <typename T>
ForwardList<T>::ForwardList() {}

template <typename T>
template <typename... Args>
ForwardList<T>::ForwardList(std::size_t n, Args&&... args) {
    Node* tail = &root;

    for (std::size_t i = 0; i < n; ++i) {
        tail->next = new Node(std::in_place, std::forward<Args>(args)...);
        tail = tail->next;
    }
}
template <typename T>
template <std::input_iterator It, std::sentinel_for<It> Sn>
    requires std::is_same<T, std::iter_value_t<It>>::value
ForwardList<T>::ForwardList(It begin, Sn end) {
    Node* tail = &root;

    while (begin != end) {
        tail->next = new Node(std::in_place, *begin);
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
    Node* tail = &root;
    const Node* their_tail = &other.root;

    while (their_tail->next != nullptr) {
        if (tail->next != nullptr) {
            tail->next->data = their_tail->next->data;
        } else {
            tail->next = new Node(std::in_place, their_tail->next->data);
        }

        tail = tail->next;
        their_tail = their_tail->next;
    }

    Node* after_tail = tail->next;
    tail->next = nullptr;

    while (after_tail != nullptr) {
        Node* next = after_tail->next;

        after_tail->destroy_data();
        delete after_tail;

        after_tail = next;
    }

    return *this;
}

template <typename T>
ForwardList<T>::~ForwardList() {
    Node* tail = root.next;

    while (tail != nullptr) {
        Node* next = tail->next;

        tail->destroy_data();
        delete tail;

        tail = next;
    }
}

template <typename T>
ForwardList<T>::iterator::iterator(Node* node) : node(node) {}

template <typename T>
auto ForwardList<T>::iterator::operator==(const iterator& other) const
    -> bool = default;

// Prefix
template <typename T>
auto ForwardList<T>::iterator::operator++() -> iterator& {
    node = node->next;
    return *this;
}

// postfix
template <typename T>
auto ForwardList<T>::iterator::operator++(int) -> iterator {
    auto old = *this;
    ++*this;
    return old;
}
template <typename T>
auto ForwardList<T>::iterator::operator*() const -> T& {
    return node->data;
}
template <typename T>
auto ForwardList<T>::iterator::operator->() const -> T* {
    return &node->data;
}

template <typename T>
ForwardList<T>::const_iterator::const_iterator(Node* node) : node(node) {}

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
// postfix
template <typename T>
auto ForwardList<T>::const_iterator::operator++(int) -> const_iterator {
    auto old = *this;
    ++*this;
    return old;
}
template <typename T>
auto ForwardList<T>::const_iterator::operator*() const -> const T& {
    return node->data;
}
template <typename T>
auto ForwardList<T>::const_iterator::operator->() const -> const T* {
    return &node->data;
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
    return root.next->data;
}
template <typename T>
auto ForwardList<T>::front() const -> const T& {
    return root.next->data;
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
auto ForwardList<T>::emplace_after(iterator it, Args&&... args) -> void {
    Node* new_node = new Node(std::in_place, std::forward<Args>(args)...);
    new_node->next = it.node->next;
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
        Node* new_next = it.node->next->next;

        it.node->next->destroy_data();
        delete it.node->next;

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
