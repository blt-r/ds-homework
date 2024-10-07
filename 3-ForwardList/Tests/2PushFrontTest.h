#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct PushFrontTest {
    PushFrontTest() {
        ForwardList<int> lst;
        lst.push_front(1);
        assertBool(!lst.empty(), __LINE__, __FILE__);
        assertEqual(lst.front(), 1, __LINE__, __FILE__);

        lst.push_front(2);
        assertBool(!lst.empty(), __LINE__, __FILE__);
        assertEqual(lst.front(), 2, __LINE__, __FILE__);

        lst.push_front(3);
        assertBool(!lst.empty(), __LINE__, __FILE__);
        assertEqual(lst.front(), 3, __LINE__, __FILE__);
    }
};

static PushFrontTest pushFrontTest;
}  // namespace test