#pragma once
#include "../List.h"
#include "CustomAsserts.h"

namespace test {
static std::size_t destructorCounter = 0;
struct TestClassForErase {
    ~TestClassForErase() { ++destructorCounter; }
};

struct EraseTest {
    EraseTest() {
        List<int> original_list{9, 5, 1, 2, 5, 3, 7};
        List<int> expected_lst1{9, 5, 1, 2, 3, 7};
        List<int> expected_lst2{9, 5, 1, 2, 3};
        List<int> expected_lst3{9, 1, 2, 3};
        List<int> expected_lst4{1, 2, 3};

        auto it1 = original_list.begin();
        for (std::size_t i = 0; i < 4; ++i)
            ++it1;
        original_list.erase(it1);
        assertBool(original_list == expected_lst1, __LINE__, __FILE__);

        auto it2 = original_list.begin();
        for (std::size_t i = 0; i < 5; ++i)
            ++it2;
        original_list.erase(it2);
        assertBool(original_list == expected_lst2, __LINE__, __FILE__);

        auto it3 = original_list.begin();
        ++it3;
        original_list.erase(it3);
        assertBool(original_list == expected_lst3, __LINE__, __FILE__);

        auto it4 = original_list.begin();
        original_list.erase(it4);
        assertBool(original_list == expected_lst4, __LINE__, __FILE__);
    }
};

static EraseTest eraseTest;
}  // namespace test
