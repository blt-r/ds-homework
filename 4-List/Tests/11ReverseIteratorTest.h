#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct ReverseIteratorTest {
    ReverseIteratorTest() {
        List<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(4);

        List<int>::reverse_iterator it = lst.rbegin();
        assertEqual(*it, 4, __LINE__, __FILE__);
        ++it;
        assertEqual(*it, 3, __LINE__, __FILE__);
        assertEqual(*++it, 2, __LINE__, __FILE__);
        *it = 9;
        assertEqual(*it++, 9, __LINE__, __FILE__);
        assertEqual(*it, 1, __LINE__, __FILE__);
        assertBool(it++ != lst.rend(), __LINE__, __FILE__);
        assertBool(it == lst.rend(), __LINE__, __FILE__);
        --it;
        assertBool(*it == 1, __LINE__, __FILE__);
        assertBool(*(it--) == 1, __LINE__, __FILE__);
        assertBool(*--it == 3, __LINE__, __FILE__);
        assertBool(it != lst.rbegin(), __LINE__, __FILE__);
        --it;
        assertBool(it == lst.rbegin(), __LINE__, __FILE__);
    }
};

static ReverseIteratorTest reverseIteratorTest;
}  // namespace test
