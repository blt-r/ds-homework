#pragma once
#include "../RationalNumber.h"
#include "CustomAsserts.h"

namespace test {
struct Test5 {
    Test5() {
        yourname::RationalNumber<int> rationalNumber4(10, 120);
        yourname::RationalNumber<int> rationalNumber5(-7, -2);
        yourname::RationalNumber<int> rationalNumber6(-5, 4);
        yourname::RationalNumber<int> rationalNumber7(9, -10);

        assertLexicallyEqual(rationalNumber4, "1/12", __LINE__, __FILE__);
        assertLexicallyEqual(rationalNumber5, "7/2", __LINE__, __FILE__);
        assertLexicallyEqual(rationalNumber6, "-5/4", __LINE__, __FILE__);
        assertLexicallyEqual(rationalNumber7, "-9/10", __LINE__, __FILE__);
    }
};

static Test5 test5;
}  // namespace test
