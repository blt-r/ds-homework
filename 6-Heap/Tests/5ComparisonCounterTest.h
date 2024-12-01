#pragma once
#include <cmath>
#include <vector>
#include "../HeapFunctions.h"
#include "CustomAsserts.h"

namespace test {
struct ComparisonCounterTest {
    ComparisonCounterTest() {
        constexpr std::size_t n_iter = 1000;
        constexpr std::size_t log_n_iter = std::bit_width(n_iter) - 1;

        std::size_t comparisons = 0;
        auto isGreater = [&comparisons](int a, int b) {
            ++comparisons;
            return a > b;
        };

        std::vector<int> vectorHeap;
        for (std::size_t i = n_iter; i > 0; --i) {
            vectorHeap.push_back(i);
            pushHeap(vectorHeap.begin(), vectorHeap.end(), isGreater);
        }
        assertLess(comparisons, n_iter * log_n_iter, __LINE__, __FILE__);

        for (std::size_t i = 0; i < n_iter; ++i)
            vectorHeap[i] = n_iter - i;

        comparisons = 0;
        makeHeap(vectorHeap.begin(), vectorHeap.end(), isGreater);
        assertLess(comparisons, 3 * n_iter, __LINE__, __FILE__);

        comparisons = 0;
        for (std::size_t i = 0; i < n_iter; ++i) {
            popHeap(vectorHeap.begin(), vectorHeap.end(), isGreater);
            vectorHeap.pop_back();
        }

        assertLess(comparisons, 2 * n_iter * log_n_iter, __LINE__, __FILE__);
    }
};

static ComparisonCounterTest comparisonCounterTest;
}  // namespace test
