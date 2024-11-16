#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct BasicConstructorsTest {
    BasicConstructorsTest() {
        Set set;
        assertBool(set.empty(), __LINE__, __FILE__);
        assertEqual(set.size(), size_t(0), __LINE__, __FILE__);
    }
};

static BasicConstructorsTest basicConstructorsTest;
}  // namespace test
