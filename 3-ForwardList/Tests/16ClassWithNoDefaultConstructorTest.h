#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {

struct TestClassWithoutDefaultConstructor {
    int val1;
    double val2;
    char val3;

    TestClassWithoutDefaultConstructor(int val1, double val2, char val3)
        : val1(val1), val2(val2), val3(val3) {}
};

struct ClassWithoutDefaultConstructorTest {
    ClassWithoutDefaultConstructorTest() {
        ForwardList<test::TestClassWithoutDefaultConstructor> lst;
        lst.push_front(test::TestClassWithoutDefaultConstructor(7, 3.14, 'k'));
        lst.push_front(test::TestClassWithoutDefaultConstructor(2, 2.71, 'p'));
        lst.push_front(test::TestClassWithoutDefaultConstructor(3, 1.61, 'z'));
        auto it = lst.before_begin();
        ++it;
        assertEqual(it->val1, 3, __LINE__, __FILE__);
        assertEqual(it->val2, 1.61, __LINE__, __FILE__);
        assertEqual(it->val3, 'z', __LINE__, __FILE__);
    }
};

static ClassWithoutDefaultConstructorTest classWithoutDefaultConstructorTest;
}  // namespace test
