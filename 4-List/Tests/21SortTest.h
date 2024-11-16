#pragma once
#include "../List.h"
#include "CustomAsserts.h"

namespace test {
struct SortTest {
    SortTest() {
        List<int> lst{6, 5, 1, 2, 4, 3, 7};

        lst.sort();

        auto it = lst.begin();

        for (int i = 1; i <= 7; ++i) {
            assertEqual(*it, i, __LINE__, __FILE__);
            ++it;
        }
    }
};

static SortTest sortTest;
}  // namespace test
