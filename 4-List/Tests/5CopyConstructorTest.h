#pragma once
#include <type_traits>
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct CopyConstructorTest {
    CopyConstructorTest() {
        assertBool(std::is_copy_constructible<List<int>>(), __LINE__, __FILE__);

        List<int> lst1;
        lst1.push_front(1);
        lst1.push_front(2);
        lst1.push_front(3);
        List<int> lst2(lst1);

        assertBool(lst1 == lst2, __LINE__, __FILE__);

        lst1.front() = 10;
        assertBool(lst1 != lst2, __LINE__, __FILE__);

        assertEqual(lst1.front(), 10, __LINE__, __FILE__);
        lst1.pop_front();
        assertEqual(lst1.front(), 2, __LINE__, __FILE__);
        lst1.pop_front();
        assertEqual(lst1.front(), 1, __LINE__, __FILE__);

        assertEqual(lst2.front(), 3, __LINE__, __FILE__);
        lst2.pop_front();
        assertEqual(lst2.front(), 2, __LINE__, __FILE__);
        lst2.pop_front();
        assertEqual(lst2.front(), 1, __LINE__, __FILE__);
    }
};

static CopyConstructorTest copyConstructorTest;
}  // namespace test
