#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct DestructorWithAssignmentTest {
    DestructorWithAssignmentTest() {
        ForwardList<int> lst1(10);
        ForwardList<int> lst2(20);

        lst2 = lst1;

        assertEqual(lst1.front(), 0, __LINE__, __FILE__);
        assertEqual(lst2.front(), 0, __LINE__, __FILE__);
        assertBool(&lst1.front() != &lst2.front(), __LINE__, __FILE__);
    }
};

static DestructorWithAssignmentTest destructorWithAssignmentTest;
}  // namespace test