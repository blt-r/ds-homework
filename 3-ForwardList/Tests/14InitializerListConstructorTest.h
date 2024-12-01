#pragma once
#include "../ForwardList.h"
#include "CustomAsserts.h"

namespace test {
struct InitializerListConstructorTest {
    InitializerListConstructorTest() {
        ForwardList<int> lst{1, 2, 3, 4, 5, 6};
        int value = 0;
        for (int& it : lst)
            assertEqual(it, ++value, __LINE__, __FILE__);
    }
};

static InitializerListConstructorTest initializerListConstructorTest;
}  // namespace test
