#pragma once
#include "../List.h"
#include "CustomAsserts.h"

namespace test {
struct InitializerListConstructorTest {
    InitializerListConstructorTest() {
        List<int> lst{1, 2, 3, 4, 5, 6};
        int value = 0;
        for (int it : lst)
            assertEqual(it, ++value, __LINE__, __FILE__);
    }
};

static InitializerListConstructorTest initializerListConstructorTest;
}  // namespace test
