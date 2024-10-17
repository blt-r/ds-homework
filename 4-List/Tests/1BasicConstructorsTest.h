#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct BasicConstructorsTest {
    BasicConstructorsTest() {
        List<double> lst1;
        assertBool(lst1.empty(), __LINE__, __FILE__);

        List<int> lst2(10);
        assertBool(!lst2.empty(), __LINE__, __FILE__);
        assertEqual(lst2.front(), 0, __LINE__, __FILE__);
        lst2.front() = 1;
        assertEqual(lst2.front(), 1, __LINE__, __FILE__);
        lst2.back() = 420;
        assertEqual(lst2.back(), 420, __LINE__, __FILE__);

        List<char> lst3(30, 'x');
        assertBool(!lst3.empty(), __LINE__, __FILE__);
        assertEqual(lst3.front(), 'x', __LINE__, __FILE__);
        assertEqual(lst3.back(), 'x', __LINE__, __FILE__);
        assertEqual(lst3.size(), std::size_t(30), __LINE__, __FILE__);
    }
};

static BasicConstructorsTest basicConstructorsTest;
}  // namespace test
