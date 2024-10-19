#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct ConstIteratorTest {
    ConstIteratorTest() {
        ForwardList<int> lst;
        lst.push_front(1);
        lst.push_front(2);
        lst.push_front(3);
        lst.push_front(4);

        ForwardList<int>::iterator it = lst.begin();
        assertEqual(*it, 4, __LINE__, __FILE__);
        ++it;
        assertEqual(*it, 3, __LINE__, __FILE__);
        assertEqual(*++it, 2, __LINE__, __FILE__);

        assertEqual(*it++, 2, __LINE__, __FILE__);
        assertEqual(*it, 1, __LINE__, __FILE__);
        assertBool(it++ != lst.end(), __LINE__, __FILE__);
        assertBool(it == lst.end(), __LINE__, __FILE__);
    }
};

static ConstIteratorTest constIteratorTest;
}  // namespace test
