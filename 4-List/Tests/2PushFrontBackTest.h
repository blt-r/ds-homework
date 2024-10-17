#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct PushFrontBackTest {
    PushFrontBackTest() {
        List<int> lst1;
        assertBool(lst1.empty(), __LINE__, __FILE__);

        lst1.push_front(1);
        assertBool(!lst1.empty(), __LINE__, __FILE__);
        assertEqual(lst1.front(), 1, __LINE__, __FILE__);
        assertEqual(lst1.back(), 1, __LINE__, __FILE__);

        lst1.push_back(2);
        assertEqual(lst1.size(), std::size_t(2), __LINE__, __FILE__);
        assertEqual(lst1.front(), 1, __LINE__, __FILE__);
        assertEqual(lst1.back(), 2, __LINE__, __FILE__);

        lst1.push_front(3);
        assertEqual(lst1.size(), std::size_t(3), __LINE__, __FILE__);
        assertEqual(lst1.front(), 3, __LINE__, __FILE__);
        assertEqual(lst1.back(), 2, __LINE__, __FILE__);

        lst1.push_back(4);
        assertEqual(lst1.size(), std::size_t(4), __LINE__, __FILE__);
        assertEqual(lst1.front(), 3, __LINE__, __FILE__);
        assertEqual(lst1.back(), 4, __LINE__, __FILE__);

        List<int> lst2;
        assertEqual(lst2.size(), std::size_t(0), __LINE__, __FILE__);

        lst2.push_back(7);
        assertEqual(lst2.size(), std::size_t(1), __LINE__, __FILE__);
        assertEqual(lst2.front(), 7, __LINE__, __FILE__);
        assertEqual(lst2.back(), 7, __LINE__, __FILE__);
    }
};

static PushFrontBackTest pushFrontBackTest;
}  // namespace test
