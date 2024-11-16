#pragma once
#include "../ForwardList.h"
#include "CustomAsserts.h"

namespace test {
struct PopFrontTest {
    PopFrontTest() {
        ForwardList<int> lst(4, 42);
        for (std::size_t i = 1; i <= 5; ++i)
            lst.push_front(i);

        for (std::size_t i = 5; i >= 1; --i) {
            assertEqual(lst.front(), int(i), __LINE__, __FILE__);
            lst.pop_front();
        }

        for (std::size_t i = 0; i < 4; ++i) {
            assertEqual(lst.front(), 42, __LINE__, __FILE__);
            lst.pop_front();
        }
        assertBool(lst.empty(), __LINE__, __FILE__);
    }
};

static PopFrontTest popFrontTest;
}  // namespace test
