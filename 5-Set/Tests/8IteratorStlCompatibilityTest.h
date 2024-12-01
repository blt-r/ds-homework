#pragma once
#include <algorithm>
#include <vector>
#include "../Set.h"
#include "CustomAsserts.h"

namespace test {
struct IteratorStlCompatibilityTest {
    IteratorStlCompatibilityTest() {
        Set set{5, 2, 3, 4, 1, 10, 20};
        std::vector<int> values{5, 2, 3, 4, 1, 10, 20};
        std::ranges::sort(values);
        std::size_t k = 0;

        for (int value : set)
            assertEqual(value, values[k++], __LINE__, __FILE__);

        auto it = std::ranges::find(set, 30);
        assertBool(it == set.end(), __LINE__, __FILE__);
    }
};

static IteratorStlCompatibilityTest iteratorStlCompatibilityTest;
}  // namespace test
