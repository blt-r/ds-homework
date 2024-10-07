#pragma once
#include "../Vector.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct ReserveAndShrinkToFitTest {
    ReserveAndShrinkToFitTest() {
        Vector<int> vec;

        assertBool(vec.empty(), __LINE__, __FILE__);
        assertEqual(vec.size(), std::size_t(0), __LINE__, __FILE__);

        vec.reserve(100);
        assertEqual(vec.capacity(), std::size_t(100), __LINE__, __FILE__);
        assertBool(vec.empty(), __LINE__, __FILE__);

        vec.shrink_to_fit();
        assertEqual(vec.capacity(), std::size_t(0), __LINE__, __FILE__);

        vec = {1, 2, 3};
        vec.reserve(100);
        assertEqual(vec.capacity(), std::size_t(100), __LINE__, __FILE__);
        vec.shrink_to_fit();
        assertEqual(vec.capacity(), std::size_t(3), __LINE__, __FILE__);
    }
};

static ReserveAndShrinkToFitTest reserveAndShrinkToFitTest;
}  // namespace test