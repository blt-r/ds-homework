#pragma once
#include "../List.h"
#include "CustomAsserts.h"

namespace test {
struct ConstIteratorTest {
    ConstIteratorTest() {
        List<int> lst;
        lst.push_front(1);
        lst.push_front(2);
        lst.push_front(3);
        lst.push_front(4);

        List<int>::const_iterator it = lst.cbegin();
        assertEqual(*it, 4, __LINE__, __FILE__);
        ++it;
        assertEqual(*it, 3, __LINE__, __FILE__);
        assertEqual(*++it, 2, __LINE__, __FILE__);

        assertEqual(*it++, 2, __LINE__, __FILE__);
        assertEqual(*it, 1, __LINE__, __FILE__);
        assertBool(it++ != lst.end(), __LINE__, __FILE__);
        assertBool(it == lst.end(), __LINE__, __FILE__);
        --it;
        assertBool(*it == 1, __LINE__, __FILE__);
        assertBool(*(it--) == 1, __LINE__, __FILE__);
        assertBool(*--it == 3, __LINE__, __FILE__);
        assertBool(it != lst.cbegin(), __LINE__, __FILE__);
        --it;
        assertBool(it == lst.cbegin(), __LINE__, __FILE__);
    }
};

static ConstIteratorTest constIteratorTest;
}  // namespace test
