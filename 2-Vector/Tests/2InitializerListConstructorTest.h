#pragma once
#include "../Vector.h"
#include "CustomAsserts.h"

namespace test {
struct InitializerListConstructorTest {
    InitializerListConstructorTest() {
        Vector<int> vec{1, 2, 3};

        assertEqual(vec.size(), std::size_t(3), __LINE__, __FILE__);
        assertEqual(vec[0], 1, __LINE__, __FILE__);
        assertEqual(vec[1], 2, __LINE__, __FILE__);
        assertEqual(vec[2], 3, __LINE__, __FILE__);
    }
};

static InitializerListConstructorTest initializerListConstructorTest;
}  // namespace test
