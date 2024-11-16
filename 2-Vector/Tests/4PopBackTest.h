#pragma once
#include "../Vector.h"
#include "CustomAsserts.h"

namespace test {
struct PopBackTest {
    PopBackTest() {
        Vector<int> vec{1, 2, 3};
        vec.pop_back();

        assertEqual(vec.size(), std::size_t(2), __LINE__, __FILE__);
        assertEqual(vec[0], 1, __LINE__, __FILE__);
        assertEqual(vec[1], 2, __LINE__, __FILE__);
    }
};

static PopBackTest popBackTest;
}  // namespace test
