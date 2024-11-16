#pragma once
#include <iostream>
#include "../RationalNumber.h"
#include "CustomAsserts.h"

namespace test {
struct Test0 {
    Test0() {
        // Represents 4/3.
        yourname::RationalNumber<int> rationalNumber1(4, 3);
        // Represents 5/1.
        yourname::RationalNumber<int> rationalNumber2(5);
        // Represents 0/1
        yourname::RationalNumber<int> rationalNumber3;

        rationalNumber1 += rationalNumber2;
        assertLexicallyEqual(rationalNumber1, "19/3", __LINE__, __FILE__);

        rationalNumber1 -= rationalNumber2;
        assertLexicallyEqual(rationalNumber1, "4/3", __LINE__, __FILE__);

        rationalNumber1 *= rationalNumber2;
        assertLexicallyEqual(rationalNumber1, "20/3", __LINE__, __FILE__);

        rationalNumber1 /= rationalNumber2;
        assertLexicallyEqual(rationalNumber1, "4/3", __LINE__, __FILE__);

        assertLexicallyEqual(rationalNumber3++, "0/1", __LINE__, __FILE__);
        assertLexicallyEqual(++rationalNumber3, "2/1", __LINE__, __FILE__);
    }
};

static Test0 test0;
}  // namespace test
