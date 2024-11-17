#pragma once
#include "../Vector.h"
#include "CustomAsserts.h"

namespace test {
struct ReserveAndShrinkToFitTest {
    ReserveAndShrinkToFitTest() {
        Vector<int> vec;

        assertBool(vec.empty(), __LINE__, __FILE__);
        assertEqual(vec.size(), 0u, __LINE__, __FILE__);

        vec.reserve(100);
        assertEqual(vec.capacity(), 100u, __LINE__, __FILE__);
        assertBool(vec.empty(), __LINE__, __FILE__);

        vec.shrink_to_fit();
        assertEqual(vec.capacity(), 0u, __LINE__, __FILE__);

        vec = {1, 2, 3};
        vec.reserve(100);
        assertEqual(vec.capacity(), 100u, __LINE__, __FILE__);
        vec.shrink_to_fit();
        assertEqual(vec.capacity(), 3u, __LINE__, __FILE__);
    }
};

static ReserveAndShrinkToFitTest reserveAndShrinkToFitTest;
}  // namespace test
