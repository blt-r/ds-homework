#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {

struct TestClassWithDefaultConstructor {
    int val1;
    double val2;
    char val3;

    TestClassWithDefaultConstructor() : val1{}, val2{}, val3{} {}

    TestClassWithDefaultConstructor(int val1, double val2, char val3)
        : val1(val1), val2(val2), val3(val3) {}

    TestClassWithDefaultConstructor(char val3, int val1)
        : val1(val1), val2(0.), val3(val3) {}
};

struct EmplaceFrontTest {
    EmplaceFrontTest() {
        ForwardList<TestClassWithDefaultConstructor> lst;

        lst.emplace_front(10, 20.3, 'x');
        lst.emplace_front();
        lst.emplace_front('s', 10);

        std::size_t count = 0;
        while (!lst.empty()) {
            lst.pop_front();
            ++count;
        }

        assertEqual(count, std::size_t(3), __LINE__, __FILE__);
    }
};

static EmplaceFrontTest emplaceFrontTest;
}  // namespace test
