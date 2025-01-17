#pragma once
#include "../Vector.h"
#include "CustomAsserts.h"

namespace test {

struct TestClassWithoutCopyConstructor {
    int val1;
    double val2;
    char val3;

    TestClassWithoutCopyConstructor(int val1, double val2, char val3)
        : val1(val1), val2(val2), val3(val3) {}

    TestClassWithoutCopyConstructor(
        const TestClassWithoutCopyConstructor& other) = delete;

    TestClassWithoutCopyConstructor(
        const TestClassWithoutCopyConstructor&& other) noexcept
        : val1(other.val1), val2(other.val2), val3(other.val3) {}
};

struct ClassWithoutCopyConstructorTest {
    ClassWithoutCopyConstructorTest() {
        Vector<test::TestClassWithoutCopyConstructor> vec3;
        for (std::size_t i = 0; i < 100; ++i)
            vec3.emplace_back(i, 20.3, 'x');

        test::assertEqual(vec3.size(), 100u, __LINE__, __FILE__);
    }
};

static ClassWithoutCopyConstructorTest classWithoutCopyConstructorTest;
}  // namespace test
