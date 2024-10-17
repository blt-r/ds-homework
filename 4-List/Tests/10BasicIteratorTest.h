#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct BasicIteratorTest {
    BasicIteratorTest() {
        List<int> lst;
        lst.push_front(1);
        lst.push_front(2);
        lst.push_front(3);
        lst.push_front(4);

        List<int>::iterator it = lst.begin();
        assertEqual(*it, 4, __LINE__, __FILE__);
        ++it;
        assertEqual(*it, 3, __LINE__, __FILE__);
        assertEqual(*++it, 2, __LINE__, __FILE__);
        *it = 9;
        assertEqual(*it++, 9, __LINE__, __FILE__);
        assertEqual(*it, 1, __LINE__, __FILE__);
        assertBool(it++ != lst.end(), __LINE__, __FILE__);
        assertBool(it == lst.end(), __LINE__, __FILE__);
        --it;
        assertBool(*it == 1, __LINE__, __FILE__);
        assertBool(*(it--) == 1, __LINE__, __FILE__);
        assertBool(*--it == 3, __LINE__, __FILE__);
        assertBool(it != lst.begin(), __LINE__, __FILE__);
        --it;
        assertBool(it == lst.begin(), __LINE__, __FILE__);
    }
};

static BasicIteratorTest basicIteratorTest;
}  // namespace test