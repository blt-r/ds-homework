#pragma once
#include <compare>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <utility>

// List's representation is actually circular,
// so list with A, B, and C will look like:
//     -> A <-> B <-> C <-> nullnode <-
// The List just contains nullnode as its only data member,
// which holds prev and next pointers.
// In empty list both next and prev of nullnode are pointing to itself.
template <typename T>
class List {
    struct NodeHeader {
        NodeHeader* next;
        NodeHeader* prev;

        NodeHeader(NodeHeader* prev, NodeHeader* next);
    };
    struct Node : NodeHeader {
        T data;

        template <typename... Args>
            requires requires(Args... args) { T(std::forward<Args>(args)...); }
        Node(NodeHeader* prev, NodeHeader* next, Args&&... args);
    };

    NodeHeader nullnode;

   public:
    List();
    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    explicit List(std::size_t n, Args&&... args);

    template <std::input_iterator It, std::sentinel_for<It> Sn>
        requires std::constructible_from<std::iter_value_t<It>, T>
    List(It begin, Sn end);
    List(std::initializer_list<T> list);

    List(const List& other);
    auto operator=(const List& other) -> List&;
    ~List();

    class iterator {
        friend class List;
        NodeHeader* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        explicit iterator(NodeHeader* node);
        iterator();  // this iterator will be invalid
        auto operator==(const iterator& other) const -> bool;
        auto operator++() -> iterator&;    // Prefix
        auto operator++(int) -> iterator;  // Postfix
        auto operator--() -> iterator&;    // Prefix
        auto operator--(int) -> iterator;  // Postfix
        auto operator*() const -> T&;
        auto operator->() const -> T*;
    };
    static_assert(std::bidirectional_iterator<iterator>);
    static_assert(std::output_iterator<iterator, T>);

    class const_iterator {
        friend class List;
        NodeHeader* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;

        explicit const_iterator(NodeHeader* node);
        const_iterator();  // this iterator will be invalid
        const_iterator(iterator it);
        auto operator==(const const_iterator& other) const -> bool;
        auto operator++() -> const_iterator&;    // Prefix
        auto operator++(int) -> const_iterator;  // Postfix
        auto operator--() -> const_iterator&;    // Prefix
        auto operator--(int) -> const_iterator;  // Postfix
        auto operator*() const -> const T&;
        auto operator->() const -> const T*;
    };
    static_assert(std::bidirectional_iterator<const_iterator>);

    auto begin() -> iterator;
    auto end() -> iterator;
    auto begin() const -> const_iterator;
    auto end() const -> const_iterator;
    auto cbegin() const -> const_iterator;
    auto cend() const -> const_iterator;

    class reverse_iterator {
        friend class List;
        NodeHeader* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        explicit reverse_iterator(NodeHeader* node);
        reverse_iterator();  // this iterator will be invalid
        auto operator==(const reverse_iterator& other) const -> bool;
        auto operator++() -> reverse_iterator&;    // Prefix
        auto operator++(int) -> reverse_iterator;  // Postfix
        auto operator--() -> reverse_iterator&;    // Prefix
        auto operator--(int) -> reverse_iterator;  // Postfix
        auto operator*() const -> T&;
        auto operator->() const -> T*;
    };
    static_assert(std::bidirectional_iterator<reverse_iterator>);
    static_assert(std::output_iterator<reverse_iterator, T>);

    class const_reverse_iterator {
        friend class List;
        NodeHeader* node;

       public:
        using difference_type = std::ptrdiff_t;
        using value_type = const T;

        explicit const_reverse_iterator(NodeHeader* node);
        const_reverse_iterator();  // this iterator will be invalid
        const_reverse_iterator(reverse_iterator it);
        auto operator==(const const_reverse_iterator& other) const -> bool;
        auto operator++() -> const_reverse_iterator&;    // Prefix
        auto operator++(int) -> const_reverse_iterator;  // Postfix
        auto operator--() -> const_reverse_iterator&;    // Prefix
        auto operator--(int) -> const_reverse_iterator;  // Postfix
        auto operator*() const -> const T&;
        auto operator->() const -> const T*;
    };
    static_assert(std::bidirectional_iterator<const_reverse_iterator>);

    auto rbegin() -> reverse_iterator;
    auto rend() -> reverse_iterator;
    auto rbegin() const -> const_reverse_iterator;
    auto rend() const -> const_reverse_iterator;
    auto crbegin() const -> const_reverse_iterator;
    auto crend() const -> const_reverse_iterator;

    auto operator==(const List& other) const -> bool;

    auto empty() -> bool;
    auto front() -> T&;
    auto front() const -> const T&;
    auto back() -> T&;
    auto back() const -> const T&;
    auto size() -> std::size_t;

    template <typename... Args>
        requires requires(Args... args) { T(std::forward<Args>(args)...); }
    auto emplace(const_iterator it, Args&&... args) -> void;
    auto insert(const_iterator it, const T& item) -> void;
    auto push_front(const T& item) -> void;
    auto push_back(const T& item) -> void;
    auto erase(const_iterator it) -> const_iterator;
    auto erase(iterator it) -> iterator;
    auto pop_front() -> void;
    auto pop_back() -> void;
    auto clear() -> void;

    // Merges two sorted lists
    auto merge(const List& other) -> void;
    auto pop_and_insert(iterator pop_from, iterator insert_to) -> iterator;

    auto insertion_sort() -> void
        requires std::three_way_comparable<T>;
    auto quick_sort() -> void  // always faster
        requires std::swappable<T> && std::three_way_comparable<T>;

    auto sort() -> void;
};

template <typename T>
List<T>::NodeHeader::NodeHeader(NodeHeader* prev, NodeHeader* next)
    : next(next), prev(prev) {}

template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
List<T>::Node::Node(NodeHeader* prev, NodeHeader* next, Args&&... args)
    : NodeHeader(prev, next), data(std::forward<Args>(args)...) {}

template <typename T>
List<T>::List() : nullnode(&nullnode, &nullnode) {}  // emptty list

template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
List<T>::List(std::size_t n, Args&&... args) : List() {
    for (std::size_t i = 0; i < n; ++i) {
        emplace(end(), std::forward<Args>(args)...);
    }
}

template <typename T>
template <std::input_iterator It, std::sentinel_for<It> Sn>
    requires std::constructible_from<std::iter_value_t<It>, T>
List<T>::List(It begin, Sn end) : List() {
    while (begin != end) {
        push_back(*begin);
        ++begin;
    }
}

template <typename T>
List<T>::List(std::initializer_list<T> list) : List(list.begin(), list.end()) {}

template <typename T>
List<T>::List(const List& other) : List(other.begin(), other.end()) {}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (&other == this) {
        return *this;
    }

    iterator it = begin();

    for (const T& el : other) {
        if (it == end()) {
            emplace(it, el);
        } else {
            *it = el;
            ++it;
        }
    }

    while (it != end()) {
        it = erase(it);
    }

    return *this;
}

template <typename T>
List<T>::~List() {
    NodeHeader* current = nullnode.next;

    while (current != &nullnode) {
        NodeHeader* next = current->next;
        delete static_cast<Node*>(current);
        current = next;
    }
}

template <typename T>
auto List<T>::empty() -> bool {
    return nullnode.prev == &nullnode;
}
template <typename T>
auto List<T>::front() -> T& {
    return static_cast<Node*>(nullnode.next)->data;
}
template <typename T>
auto List<T>::front() const -> const T& {
    return static_cast<Node*>(nullnode.next)->data;
}
template <typename T>
auto List<T>::back() -> T& {
    return static_cast<Node*>(nullnode.prev)->data;
}
template <typename T>
auto List<T>::back() const -> const T& {
    return static_cast<Node*>(nullnode.prev)->data;
}

template <typename T>
auto List<T>::size() -> std::size_t {
    return std::distance(begin(), end());
}

template <typename T>
auto List<T>::operator==(const List& other) const -> bool {
    return std::equal(begin(), end(), other.begin(), other.end());
}

template <typename T>
template <typename... Args>
    requires requires(Args... args) { T(std::forward<Args>(args)...); }
auto List<T>::emplace(const_iterator it, Args&&... args) -> void {
    Node* new_node =
        new Node(it.node->prev, it.node, std::forward<Args>(args)...);
    it.node->prev->next = new_node;
    it.node->prev = new_node;
}

template <typename T>
auto List<T>::insert(const_iterator it, const T& item) -> void {
    emplace(it, item);
}

template <typename T>
auto List<T>::push_front(const T& item) -> void {
    emplace(begin(), item);
}

template <typename T>
auto List<T>::push_back(const T& item) -> void {
    emplace(end(), item);
}

template <typename T>
auto List<T>::erase(const_iterator it) -> const_iterator {
    it.node->prev->next = it.node->next;
    it.node->next->prev = it.node->prev;
    iterator new_it = iterator(it.node->next);
    delete static_cast<Node*>(it.node);
    return new_it;
}

template <typename T>
auto List<T>::erase(iterator it) -> iterator {
    it.node->prev->next = it.node->next;
    it.node->next->prev = it.node->prev;
    iterator new_it = iterator(it.node->next);
    delete static_cast<Node*>(it.node);
    return new_it;
}

template <typename T>
auto List<T>::pop_front() -> void {
    erase(begin());
}
template <typename T>
auto List<T>::pop_back() -> void {
    erase(std::prev(end()));
}

template <typename T>
auto List<T>::clear() -> void {
    std::destroy_at(this);
    std::construct_at(this);
}

template <typename T>
auto List<T>::merge(const List& other) -> void {
    auto me = begin();
    auto him = other.begin();

    while (him != other.end()) {
        if (me == end() || *me >= *him) {
            emplace(me, *him);
            ++him;
        } else if (me != end()) {
            ++me;
        }
    }
}

template <typename T>
auto List<T>::pop_and_insert(iterator pop_from, iterator insert_to)
    -> iterator {
    auto after_poped = pop_from.node->next;

    pop_from.node->prev->next = pop_from.node->next;
    pop_from.node->next->prev = pop_from.node->prev;

    pop_from.node->next = insert_to.node;
    pop_from.node->prev = insert_to.node->prev;

    insert_to.node->prev->next = pop_from.node;
    insert_to.node->prev = pop_from.node;

    return iterator(after_poped);
}

template <typename T>
auto List<T>::insertion_sort() -> void
    requires std::three_way_comparable<T>
{
    if (empty()) {
        return;
    }

    auto pivot = std::next(begin());

    while (pivot != end()) {
        auto current = pivot;

        while (current != begin() && *pivot < *std::prev(current)) {
            --current;
        }

        if (current == pivot) {
            ++pivot;
        } else {
            pivot = pop_and_insert(pivot, current);
        }
    }
}

template <std::forward_iterator It>
    requires std::swappable<std::iter_value_t<It>> &&
             std::three_way_comparable<std::iter_value_t<It>>
auto partition(It from, It to) -> It {
    if (from == to || std::next(from) == to) {
        return from;
    }

    auto pivot = from;
    auto wall = from;

    for (auto it = std::next(from); it != to; ++it) {
        if (*it < *pivot) {
            ++wall;
            std::swap(*it, *wall);
        }
    }

    std::swap(*pivot, *wall);

    return wall;
}

template <std::forward_iterator It>
    requires std::swappable<std::iter_value_t<It>> &&
             std::three_way_comparable<std::iter_value_t<It>>
auto quick_sort_rec(It from, It to) -> void {
    if (from == to || std::next(from) == to) {
        return;
    }
    auto pivot = partition(from, to);

    quick_sort_rec(from, pivot);
    quick_sort_rec(std::next(pivot), to);
}

template <typename T>
auto List<T>::quick_sort() -> void
    requires std::swappable<T> && std::three_way_comparable<T>
{
    quick_sort_rec(begin(), end());
}

template <typename T>
auto List<T>::sort() -> void {
    quick_sort();
}
// ## List::iterator
template <typename T>
List<T>::iterator::iterator(NodeHeader* node) : node(node) {}

template <typename T>
List<T>::iterator::iterator()
    : node(nullptr) {}  // this iterator will be invalid

template <typename T>
auto List<T>::iterator::operator==(const iterator& other) const
    -> bool = default;

template <typename T>
auto List<T>::iterator::operator++() -> iterator& {
    node = node->next;
    return *this;
}

template <typename T>
auto List<T>::iterator::operator++(int) -> iterator {
    auto old = *this;
    ++*this;
    return old;
}

template <typename T>
auto List<T>::iterator::operator--() -> iterator& {
    node = node->prev;
    return *this;
}

template <typename T>
auto List<T>::iterator::operator--(int) -> iterator {
    auto old = *this;
    --*this;
    return old;
}

template <typename T>
auto List<T>::iterator::operator*() const -> T& {
    return static_cast<Node*>(node)->data;
}

template <typename T>
auto List<T>::iterator::operator->() const -> T* {
    return &static_cast<Node*>(node)->data;
}

// ## List::const_iterator

template <typename T>
List<T>::const_iterator::const_iterator(NodeHeader* node) : node(node) {}

template <typename T>
List<T>::const_iterator::const_iterator()
    : node(nullptr) {}  // this iterator will be invalid

template <typename T>
List<T>::const_iterator::const_iterator(iterator it) : node(it.node) {}

template <typename T>
auto List<T>::const_iterator::operator==(const const_iterator& other) const
    -> bool = default;

template <typename T>
auto List<T>::const_iterator::operator++() -> const_iterator& {
    node = node->next;
    return *this;
}

template <typename T>
auto List<T>::const_iterator::operator++(int) -> const_iterator {
    auto old = *this;
    ++*this;
    return old;
}

template <typename T>
auto List<T>::const_iterator::operator--() -> const_iterator& {
    node = node->prev;
    return *this;
}

template <typename T>
auto List<T>::const_iterator::operator--(int) -> const_iterator {
    auto old = *this;
    --*this;
    return old;
}

template <typename T>
auto List<T>::const_iterator::operator*() const -> const T& {
    return static_cast<const Node*>(node)->data;
}

template <typename T>
auto List<T>::const_iterator::operator->() const -> const T* {
    return &static_cast<const Node*>(node)->data;
}

template <typename T>
auto List<T>::begin() -> iterator {
    return iterator(nullnode.next);
}

template <typename T>
auto List<T>::end() -> iterator {
    return iterator(&nullnode);
}

template <typename T>
auto List<T>::begin() const -> const_iterator {
    return const_iterator(nullnode.next);
}

template <typename T>
auto List<T>::end() const -> const_iterator {
    return const_iterator(const_cast<NodeHeader*>(&nullnode));
}

template <typename T>
auto List<T>::cbegin() const -> const_iterator {
    return begin();
}

template <typename T>
auto List<T>::cend() const -> const_iterator {
    return end();
}

// ## List::reverse_iterator

template <typename T>
List<T>::reverse_iterator::reverse_iterator(NodeHeader* node) : node(node) {}

template <typename T>
List<T>::reverse_iterator::reverse_iterator()
    : node(nullptr) {}  // this iterator will be invalid

template <typename T>
auto List<T>::reverse_iterator::operator==(const reverse_iterator& other) const
    -> bool = default;

template <typename T>
auto List<T>::reverse_iterator::operator++() -> reverse_iterator& {
    node = node->prev;
    return *this;
}

template <typename T>
auto List<T>::reverse_iterator::operator++(int) -> reverse_iterator {
    auto old = *this;
    ++*this;
    return old;
}

template <typename T>
auto List<T>::reverse_iterator::operator--() -> reverse_iterator& {
    node = node->next;
    return *this;
}

template <typename T>
auto List<T>::reverse_iterator::operator--(int) -> reverse_iterator {
    auto old = *this;
    --*this;
    return old;
}

template <typename T>
auto List<T>::reverse_iterator::operator*() const -> T& {
    return static_cast<Node*>(node)->data;
}

template <typename T>
auto List<T>::reverse_iterator::operator->() const -> T* {
    return &static_cast<Node*>(node)->data;
}

// ## List::const_reverse_iterator

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(NodeHeader* node)
    : node(node) {}

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator()
    : node(nullptr) {}  // this iterator will be invalid

template <typename T>
auto List<T>::const_reverse_iterator::operator==(
    const const_reverse_iterator& other) const -> bool = default;

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(reverse_iterator it)
    : node(it.node) {}

template <typename T>
auto List<T>::const_reverse_iterator::operator++() -> const_reverse_iterator& {
    node = node->prev;
    return *this;
}

template <typename T>
auto List<T>::const_reverse_iterator::operator++(int)
    -> const_reverse_iterator {
    auto old = *this;
    ++*this;
    return old;
}

template <typename T>
auto List<T>::const_reverse_iterator::operator--() -> const_reverse_iterator& {
    node = node->next;
    return *this;
}

template <typename T>
auto List<T>::const_reverse_iterator::operator--(int)
    -> const_reverse_iterator {
    auto old = *this;
    --*this;
    return old;
}

template <typename T>
auto List<T>::const_reverse_iterator::operator*() const -> const T& {
    return static_cast<const Node*>(node)->data;
}

template <typename T>
auto List<T>::const_reverse_iterator::operator->() const -> const T* {
    return &static_cast<const Node*>(node)->data;
}

template <typename T>
auto List<T>::rbegin() -> reverse_iterator {
    return reverse_iterator(nullnode.prev);
}

template <typename T>
auto List<T>::rend() -> reverse_iterator {
    return reverse_iterator(&nullnode);
}

template <typename T>
auto List<T>::rbegin() const -> const_reverse_iterator {
    return const_reverse_iterator(nullnode.prev);
}

template <typename T>
auto List<T>::rend() const -> const_reverse_iterator {
    return const_reverse_iterator(const_cast<NodeHeader*>(&nullnode));
}

template <typename T>
auto List<T>::crbegin() const -> const_reverse_iterator {
    return rbegin();
}

template <typename T>
auto List<T>::crend() const -> const_reverse_iterator {
    return rend();
}

template <typename T>
auto operator<<(std::ostream& os, const List<T>& list) -> std::ostream& {
    auto begin = list.begin();
    auto end = list.end();

    os << '[';
    if (begin != end) {
        os << *begin;
        ++begin;
    }

    while (begin != end) {
        os << " <-> " << *begin;
        ++begin;
    }
    os << ']';
    return os;
}
