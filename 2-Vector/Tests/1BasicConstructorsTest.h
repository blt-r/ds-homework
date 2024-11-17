#pragma once
#include "../Vector.h"
#include "CustomAsserts.h"

namespace test {
struct BasicConstructorsTest {
    BasicConstructorsTest() {
        Vector<int> vec1;
        Vector<double> vec2(10);
        Vector<char> vec3(30, 'x');

        assertEqual(vec1.size(), 0u, __LINE__, __FILE__);
        assertEqual(vec2.size(), 10u, __LINE__, __FILE__);
        assertEqual(vec3.size(), 30u, __LINE__, __FILE__);
    }
};

static BasicConstructorsTest basicConstructorsTest;
}  // namespace test
