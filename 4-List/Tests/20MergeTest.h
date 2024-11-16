#pragma once
#include "../List.h"
#include "CustomAsserts.h"

namespace test {
struct MergeTest {
    MergeTest() {
        List<int> lst1{4, 6, 10, 20, 30, 34, 35};
        List<int> lst2{1, 2, 3, 7, 40, 50};
        List<int> lst1_copy = lst1;
        List<int> lst2_copy = lst2;
        List<int> expected_lst{1, 2, 3, 4, 6, 7, 10, 20, 30, 34, 35, 40, 50};

        lst1.merge(lst2);
        assertBool(lst1 == expected_lst, __LINE__, __FILE__);

        lst2_copy.merge(lst1_copy);
        assertBool(lst2_copy == expected_lst, __LINE__, __FILE__);
    }
};

static MergeTest mergeTest;
}  // namespace test
