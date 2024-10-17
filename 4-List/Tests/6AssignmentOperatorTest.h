#pragma once
#include <type_traits>
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct AssignmentOperatorTest {
    AssignmentOperatorTest() {
        assertBool(std::is_copy_assignable<List<int>>(), __LINE__, __FILE__);

        List<int> lst1;
        lst1.push_back(1);
        lst1.push_back(2);
        lst1.push_back(3);
        List<int> lst2;

        lst2 = lst1;

        assertBool(lst1 == lst2, __LINE__, __FILE__);

        lst1.back() = 10;
        assertBool(lst1 != lst2, __LINE__, __FILE__);

        assertEqual(lst1.back(), 10, __LINE__, __FILE__);
        lst1.pop_back();
        assertEqual(lst1.back(), 2, __LINE__, __FILE__);
        lst1.pop_back();
        assertEqual(lst1.back(), 1, __LINE__, __FILE__);

        assertEqual(lst2.back(), 3, __LINE__, __FILE__);
        lst2.pop_back();
        assertEqual(lst2.back(), 2, __LINE__, __FILE__);
        lst2.pop_back();
        assertEqual(lst2.back(), 1, __LINE__, __FILE__);
    }
};

static AssignmentOperatorTest assignmentOperatorTest;
}  // namespace test