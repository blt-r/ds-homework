#include <cstddef>
#include <format>
#include <iostream>

#include "Set.h"

struct Set::Node {
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    size_t level;
    int value;

    Node(int value, size_t level) : level(level), value(value) {}

    auto compute_level() -> size_t {
        size_t lh = left ? left->level : 0;
        size_t rh = right ? right->level : 0;
        return 1 + std::max(lh, rh);
    }

    auto balance() -> ssize_t {
        ssize_t lh = left ? left->level : 0;
        ssize_t rh = right ? right->level : 0;
        return lh - rh;
    }

    auto min_in_subtree() -> Node* {
        return left ? left->min_in_subtree() : this;
    }
};

Set::Set() : root(nullptr), element_count(0) {}

auto Set::rec_copy(Node* from, Node* to_parent, Node*& to) -> void {
    if (from == nullptr) {
        return;
    }

    to = new Node(from->value, from->level);
    to->parent = to_parent;

    rec_copy(from->left, to, to->left);
    rec_copy(from->right, to, to->right);
}

Set::Set(const Set& other) : root(nullptr), element_count(other.element_count) {
    rec_copy(other.root, nullptr, root);
}

auto Set::operator=(const Set& other) -> Set& {
    rec_destroy(root);
    rec_copy(other.root, nullptr, root);

    element_count = other.element_count;

    return *this;
}

auto Set::rec_destroy(Node* node) -> void {
    if (node == nullptr) {
        return;
    }

    rec_destroy(node->left);
    rec_destroy(node->right);

    delete node;
}

Set::~Set() {
    rec_destroy(root);
}

Set::Set(std::initializer_list<int> list) : Set() {
    for (int el : list) {
        insert(el);
    }
}

auto Set::operator==(const Set& other) const -> bool {
    return std::equal(begin(), end(), other.begin(), other.end());
}

auto Set::size() const -> size_t {
    return element_count;
}

auto Set::empty() const -> bool {
    return element_count == 0;
}

// |                                         |
// |    x                             y      |
// |   /  \     left_rotate(x)       / \     |
// |  T1   y       ------->         x   T3   |
// |      / \                      / \       |
// |     T2  T3                   T1  T2     |
// |                                         |
auto Set::left_rotate(Node*& x) -> void {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    y->parent = x->parent;
    x->right = T2;
    x->parent = y;

    if (T2 != nullptr) {
        T2->parent = x;
    }

    x->level = x->compute_level();
    y->level = y->compute_level();

    x = y;
}

// |                                         |
// |      x                         y        |
// |     / \     right_rotate(x)   /  \      |
// |    y   T3      ------->      T1   x     |
// |   / \                            / \    |
// |  T1  T2                         T2  T3  |
// |                                         |
auto Set::right_rotate(Node*& x) -> void {
    Node* y = x->left;
    Node* T2 = y->right;

    y->right = x;
    y->parent = x->parent;
    x->left = T2;
    x->parent = y;

    if (T2 != nullptr) {
        T2->parent = x;
    }

    x->level = x->compute_level();
    y->level = y->compute_level();

    x = y;
}

auto Set::rec_insert(Node* parent, Node*& node, int value) -> void {
    if (node == nullptr) {
        node = new Node(value, 1);
        node->parent = parent;
        element_count++;
        return;
    }

    if (value == node->value) {
        return;
    } else if (value < node->value) {
        rec_insert(node, node->left, value);
    } else {
        rec_insert(node, node->right, value);
    }

    node->level = node->compute_level();

    ssize_t balance = node->balance();

    // left left case
    if (balance > 1 && value < node->left->value) {
        right_rotate(node);
    }

    // right right case
    if (balance < -1 && value > node->right->value) {
        left_rotate(node);
    }

    // left right case
    if (balance > 1 && value > node->left->value) {
        left_rotate(node->left);
        right_rotate(node);
    }

    // right left case
    if (balance < -1 && value < node->right->value) {
        right_rotate(node->right);
        left_rotate(node);
    }
}

auto Set::insert(int value) -> void {
    rec_insert(nullptr, root, value);
}

auto Set::rec_yank(Node*& node, int value) -> Node* {
    Node* yanked = nullptr;

    if (node == nullptr) {
        return yanked;
    }

    if (value < node->value) {
        yanked = rec_yank(node->left, value);
    } else if (value > node->value) {
        yanked = rec_yank(node->right, value);
    } else if (node->left == nullptr) {
        if (node->right) {
            node->right->parent = node->parent;
        }
        yanked = node;
        node = node->right;
    } else if (node->right == nullptr) {
        if (node->left) {
            node->left->parent = node->parent;
        }
        yanked = node;
        node = node->left;
    } else {
        yanked = node;

        Node* successor = node->right->min_in_subtree();

        // this will return the successor
        rec_yank(node->right, successor->value);

        // right might have been the successor, not exist anymore
        if (node->right != nullptr) {
            node->right->parent = successor;
        }
        node->left->parent = successor;

        successor->left = node->left;
        successor->right = node->right;
        successor->parent = node->parent;

        node = successor;
    }

    if (node == nullptr) {
        return yanked;
    }

    node->level = node->compute_level();

    ssize_t balance = node->balance();

    // left left case
    if (balance > 1 && node->left->balance() >= 0) {
        right_rotate(node);
    }

    // right right case
    if (balance < -1 && node->right->balance() <= 0) {
        left_rotate(node);
    }

    // left right case
    if (balance > 1 && node->left->balance() < 0) {
        left_rotate(node->left);
        right_rotate(node);
    }

    // right left case
    if (balance < -1 && node->right->balance() > 0) {
        right_rotate(node->right);
        left_rotate(node);
    }

    return yanked;
}

auto Set::erase(int value) -> void {
    Node* yanked = rec_yank(root, value);

    if (yanked != nullptr) {
        delete yanked;
        element_count--;
    }
}

auto Set::erase(iterator it) -> iterator {
    iterator next = std::next(it);
    erase(*it);  // erase doesn't invalidate any iterators
    return next;
}

auto Set::contains(int value) -> bool {
    Node* current = root;

    while (current != nullptr) {
        if (value == current->value) {
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

auto Set::find(int value) const -> iterator {
    Node* current = root;

    while (current) {
        if (value == current->value) {
            return iterator(current);
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return iterator();
}

auto Set::upper_bound(int value) const -> iterator {
    Node* current = root;

    while (current) {
        if (current->value > value) {
            if (current->left == nullptr || current->left->value < value) {
                return iterator(current);
            }
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return iterator();
}

auto Set::lower_bound(int value) const -> iterator {
    Node* current = root;

    while (current) {
        if (current->value == value) {
            return iterator(current);
        } else if (current->value > value) {
            if (current->left == nullptr || current->left->value < value) {
                return iterator(current);
            }
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return iterator();
}

auto Set::rec_dump_graphviz(Node* node, std::ostream& os) -> void {
    if (node == nullptr) {
        return;
    }

    os << (node->parent != nullptr)
        ? std::format("  {} [label=\"{}\\nlevel={}\\nparent={}\"]\n",
                      node->value, node->value, node->level,
                      node->parent->value)
        : std::format("  {} [label=\"{}\\nlevel={}\\nparent=(null)\"]\n",
                      node->value, node->value, node->level);

    if (node->left != nullptr) {
        os << std::format("  {} -> {} [label=left]\n", node->value,
                          node->left->value);
        rec_dump_graphviz(node->left, os);
    }
    if (node->right != nullptr) {
        os << std::format("  {} -> {} [label=right]\n", node->value,
                          node->right->value);
        rec_dump_graphviz(node->right, os);
    }
}

auto Set::dump_graphviz(std::ostream& os) -> void {
    os << "digraph BST {\n";
    rec_dump_graphviz(root, os);
    os << "}\n";
}

auto Set::begin() const -> iterator {
    if (root != nullptr) {
        return iterator(root->min_in_subtree());
    } else {
        return iterator();
    }
}

auto Set::end() const -> iterator {
    return iterator();
}

Set::iterator::iterator() : node(nullptr) {}
Set::iterator::iterator(Node* node) : node(node) {}

auto Set::iterator::operator==(const iterator& other) const -> bool = default;

auto Set::iterator::operator++() -> iterator& {  // Prefix
    if (node->right != nullptr) {
        node = node->right->min_in_subtree();
        return *this;
    }

    while (node->parent != nullptr && node->parent->right == node) {
        node = node->parent;
    }

    if (node->parent == nullptr) {
        node = nullptr;
        return *this;
    }

    if (node->parent->left == node) {
        node = node->parent;
        return *this;
    }

    return *this;
}

auto Set::iterator::operator++(int) -> iterator {  // Postfix
    auto tmp = *this;
    ++*this;
    return tmp;
}

auto Set::iterator::operator*() const -> const int& {
    return node->value;
}

auto Set::iterator::operator->() const -> const int* {
    return &node->value;
}
