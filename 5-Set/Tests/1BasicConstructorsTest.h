#pragma once
#include "../Set.h"
#include "CustomAsserts.h"

namespace test {
struct BasicConstructorsTest {
    BasicConstructorsTest() {
        Set set;
        assertBool(set.empty(), __LINE__, __FILE__);
        assertEqual(set.size(), 0u, __LINE__, __FILE__);
    }
};

static BasicConstructorsTest basicConstructorsTest;
}  // namespace test
