#pragma once

#include <cstddef>
#include <ostream>
#include <stack>
#include <vector>

class Set {
  public:
    Set();
    Set(const Set& other);
    auto operator=(const Set& other) -> Set&;
    ~Set();

    Set(std::initializer_list<int> list);

    auto operator==(const Set& other) const -> bool;

    class iterator;
    auto begin() const -> iterator;
    auto end() const -> iterator;

    auto size() const -> size_t;
    auto empty() const -> bool;

    auto insert(int value) -> void;
    auto erase(int value) -> void;
    auto erase(iterator it) -> iterator;
    auto contains(int value) -> bool;
    auto find(int value) const -> iterator;
    auto upper_bound(int value) const -> iterator;
    auto lower_bound(int value) const -> iterator;

    auto dump_graphviz(std::ostream& os) -> void;

  private:
    struct Node;
    Node* root;
    size_t element_count;

    static auto rec_copy(Node* from, Node* to_parent, Node*& to) -> void;
    static auto rec_destroy(Node* node) -> void;
    auto rec_insert(Node* parent, Node*& node, int value) -> void;
    static auto rec_yank(Node*& node, int value) -> Node*;

    static auto right_rotate(Node*& x) -> void;
    static auto left_rotate(Node*& x) -> void;

    static auto rec_dump_graphviz(Node* node, std::ostream& os) -> void;
};

class Set::iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = const int;

    iterator();
    auto operator==(const iterator& other) const -> bool;
    auto operator++() -> iterator&;    // Prefix
    auto operator++(int) -> iterator;  // Postfix
    auto operator*() const -> const int&;
    auto operator->() const -> const int*;

  private:
    friend class Set;

    Node* node;

    iterator(Node* node);
};
static_assert(std::forward_iterator<Set::iterator>);

auto operator<<(std::ostream& os, const Set& set) -> std::ostream&;
