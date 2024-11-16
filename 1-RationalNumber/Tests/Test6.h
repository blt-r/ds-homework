#pragma once
#include "../RationalNumber.h"
#include "CustomAsserts.h"

namespace test {
struct Test6 {
    Test6() {
        yourname::RationalNumber<int> rationalNumber4(10, 120);
        yourname::RationalNumber<int> rationalNumber5(-7, -2);
        yourname::RationalNumber<int> rationalNumber6(-5, 4);
        yourname::RationalNumber<int> rationalNumber7(9, -10);

        assertBool(rationalNumber4 < rationalNumber5, __LINE__, __FILE__);
        assertBool(!(rationalNumber6 > rationalNumber7), __LINE__, __FILE__);
        assertBool(!(rationalNumber4 <= rationalNumber6), __LINE__, __FILE__);
        assertBool(rationalNumber5 >= rationalNumber7, __LINE__, __FILE__);
        assertBool(!(rationalNumber5 == rationalNumber4), __LINE__, __FILE__);
        assertBool(rationalNumber7 != rationalNumber6, __LINE__, __FILE__);
    }
};

static Test6 test6;
}  // namespace test
