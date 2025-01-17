#pragma once
#include <algorithm>
#include "../ForwardList.h"
#include "CustomAsserts.h"

namespace test {
struct StlCompatibilityTest {
    StlCompatibilityTest() {
        ForwardList<int> lst1{9, 5, 3, 4, 2, 5, 6, 5, 5, 4};
        auto count1 = std::count(lst1.begin(), lst1.end(), 5);
        assertEqual(count1, 4, __LINE__, __FILE__);

        auto count2 = std::count_if(lst1.begin(), lst1.end(),
                                    [](int value) { return value % 2 == 1; });
        assertEqual(count2, 6, __LINE__, __FILE__);

        ForwardList<int> lst2{4, 4, 4, 4, 4, 4};
        for (auto value : lst2) {
            assertEqual(value, 4, __LINE__, __FILE__);
        }

        assertBool(std::ranges::all_of(lst2, [](int val) { return val == 4; }),
                   __LINE__, __FILE__);
    }
};

static StlCompatibilityTest stlCompatibilityTest;
}  // namespace test
