#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct ConstReverseIteratorTest {
    ConstReverseIteratorTest() {
        List<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(4);

        List<int>::const_reverse_iterator it = lst.crbegin();
        assertEqual(*it, 4, __LINE__, __FILE__);
        ++it;
        assertEqual(*it, 3, __LINE__, __FILE__);
        assertEqual(*++it, 2, __LINE__, __FILE__);

        assertEqual(*it++, 2, __LINE__, __FILE__);
        assertEqual(*it, 1, __LINE__, __FILE__);
        assertBool(it++ != lst.crend(), __LINE__, __FILE__);
        assertBool(it == lst.crend(), __LINE__, __FILE__);
        --it;
        assertBool(*it == 1, __LINE__, __FILE__);
        assertBool(*(it--) == 1, __LINE__, __FILE__);
        assertBool(*--it == 3, __LINE__, __FILE__);
        assertBool(it != lst.crbegin(), __LINE__, __FILE__);
        --it;
        assertBool(it == lst.crbegin(), __LINE__, __FILE__);
    }
};

static ConstReverseIteratorTest constReverseIteratorTest;
}  // namespace test