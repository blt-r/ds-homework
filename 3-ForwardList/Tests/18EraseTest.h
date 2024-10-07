#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
static std::size_t destructorCounter = 0;
struct TestClassForErase {
    ~TestClassForErase() {
        if (destructorCounter != 0)
            ++destructorCounter;
    }
};

struct EraseTest {
    EraseTest() {
        ForwardList<int> original_list{9, 5, 1, 2, 5, 3, 7};
        ForwardList<int> expected_lst1{9, 5, 1, 2, 3, 7};
        ForwardList<int> expected_lst2{9, 5, 1, 2, 3};
        ForwardList<int> expected_lst3{9, 1, 2, 3};
        ForwardList<int> expected_lst4{1, 2, 3};

        auto it1 = original_list.begin();
        for (std::size_t i = 0; i < 3; ++i)
            ++it1;
        original_list.erase_after(it1);
        assertBool(original_list == expected_lst1, __LINE__, __FILE__);

        auto it2 = original_list.begin();
        for (std::size_t i = 0; i < 4; ++i)
            ++it2;
        original_list.erase_after(it2);
        assertBool(original_list == expected_lst2, __LINE__, __FILE__);

        auto it3 = original_list.begin();
        original_list.erase_after(it3);
        assertBool(original_list == expected_lst3, __LINE__, __FILE__);

        auto it4 = original_list.before_begin();
        original_list.erase_after(it4);
        assertBool(original_list == expected_lst4, __LINE__, __FILE__);

        ForwardList<TestClassForErase> erase_list(10);
        ++destructorCounter;
        erase_list.erase_after(erase_list.begin());
        assertEqual(destructorCounter, std::size_t(2), __LINE__, __FILE__);
    }
};

static EraseTest eraseTest;
}  // namespace test