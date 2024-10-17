#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct InitializerListConstructorTest {
    InitializerListConstructorTest() {
        List<int> lst{1, 2, 3, 4, 5, 6};
        int value = 0;
        for (auto it = lst.begin(); it != lst.end(); ++it)
            assertEqual(*it, ++value, __LINE__, __FILE__);
    }
};

static InitializerListConstructorTest initializerListConstructorTest;
}  // namespace test