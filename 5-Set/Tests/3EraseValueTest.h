#pragma once
#include <algorithm>
#include <vector>
#include "../Set.h"
#include "CustomAsserts.h"

namespace test {
struct EraseValueTest {
    EraseValueTest() {
        std::vector<int> values{20, 10, 30, 5, 14, 26, 40, 2,  7,  12, 19, 21,
                                28, 35, 50, 1, 6,  8,  11, 13, 17, 24, 27, 29};

        Set set;
        for (int value : values)
            set.insert(value);

        set.erase(29);
        values.erase(std::ranges::find(values, 29));

        for (int value : values)
            assertBool(set.contains(value), __LINE__, __FILE__);
        assertEqual(set.size(), values.size(), __LINE__, __FILE__);

        set.erase(2);
        values.erase(std::ranges::find(values, 2));

        for (int value : values)
            assertBool(set.contains(value), __LINE__, __FILE__);
        assertEqual(set.size(), values.size(), __LINE__, __FILE__);

        set.erase(20);
        values.erase(std::ranges::find(values, 20));

        for (int value : values)
            assertBool(set.contains(value), __LINE__, __FILE__);
        assertEqual(set.size(), values.size(), __LINE__, __FILE__);

        set.erase(14);
        values.erase(std::ranges::find(values, 14));

        for (int value : values)
            assertBool(set.contains(value), __LINE__, __FILE__);
        assertEqual(set.size(), values.size(), __LINE__, __FILE__);
    }
};

static EraseValueTest eraseValueTest;
}  // namespace test
