#pragma once

#include <iterator>

template <std::random_access_iterator It, typename Compare>
struct HeapView {
    using diff_t = std::iter_difference_t<It>;

    It first;
    diff_t size;
    Compare cmp;

    HeapView(It first, It last, Compare cmp)
        : first(first), size(last - first), cmp(cmp) {}

    // Heapifies subtree at `node` if both left and right are already heaps
    auto heapify(diff_t node) -> void {
        diff_t r = 2 * node + 1;
        diff_t l = 2 * node + 2;

        diff_t largest = node;
        if (l < size && cmp(first[largest], first[l])) {
            largest = l;
        }
        if (r < size && cmp(first[largest], first[r])) {
            largest = r;
        }

        if (largest != node) {
            std::swap(first[largest], first[node]);
            heapify(largest);
        }
    }

    auto make_heap() -> void {
        diff_t start_idx = size / 2 - 1;

        for (diff_t i = 0; i <= start_idx; ++i) {
            // heapify all the non-leaf nodes in reverse order
            heapify(start_idx - i);
        }
    }

    auto pop() -> void {
        std::swap(first[0], first[size - 1]);
        size -= 1;
        heapify(0);
    }

    auto push() -> void {
        diff_t node = size - 1;

        while (node != 0) {
            diff_t parent = (node - 1) / 2;

            if (cmp(first[node], first[parent])) {
                break;
            }

            std::swap(first[parent], first[node]);
            node = parent;
        }
    }
};

template <std::random_access_iterator It>
auto makeHeap(It first, It last) -> void {
    HeapView(first, last, std::less{}).make_heap();
}

template <std::random_access_iterator It, typename Compare>
auto makeHeap(It first, It last, Compare cmp) -> void {
    HeapView(first, last, cmp).make_heap();
}

template <std::random_access_iterator It>
auto popHeap(It first, It last) -> void {
    HeapView(first, last, std::less{}).pop();
}

template <std::random_access_iterator It, typename Compare>
auto popHeap(It first, It last, Compare cmp) -> void {
    HeapView(first, last, cmp).pop();
}

template <std::random_access_iterator It>
auto pushHeap(It first, It last) -> void {
    HeapView(first, last, std::less{}).push();
}

template <std::random_access_iterator It, typename Compare>
auto pushHeap(It first, It last, Compare cmp) -> void {
    HeapView(first, last, cmp).push();
}
