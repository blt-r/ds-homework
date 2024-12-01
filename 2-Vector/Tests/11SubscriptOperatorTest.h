#pragma once
#include "../Vector.h"
#include "CustomAsserts.h"

namespace test {
struct TestClassForSubscriptOperator {
    auto getVal() -> std::string { return "getVal"; }

    auto getVal() const -> std::string { return "getVal const"; }
};

struct SubscriptOperatorTest {
    SubscriptOperatorTest() {
        Vector<TestClassForSubscriptOperator> vec1(10);
        const auto& vec2 = vec1;

        using namespace std::string_literals;
        assertEqual(vec1[0].getVal(), "getVal"s, __LINE__, __FILE__);
        assertEqual(vec2[0].getVal(), "getVal const"s, __LINE__, __FILE__);
    }
};

static SubscriptOperatorTest subscriptOperatorTest;
}  // namespace test
