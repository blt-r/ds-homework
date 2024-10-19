#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct ClearTest {
    ClearTest() {
        ForwardList<int> lst(3, 10);
        lst.clear();
        assertBool(lst.empty(), __LINE__, __FILE__);
    }
};

static ClearTest clearTest;
}  // namespace test
