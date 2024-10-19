#pragma once
#include "../ForwardList.h"
#include "Fixtures/CustomAsserts.h"

namespace test {
struct InsertTest {
    InsertTest() {
        ForwardList<int> original_list{9, 5, 1, 2, 5, 3, 7};
        ForwardList<int> expected_lst1{9, 5, 1, 2, 8, 5, 3, 7};
        ForwardList<int> expected_lst2{9, 5, 1, 2, 8, 5, 3, 7, 2};
        ForwardList<int> expected_lst3{9, 4, 5, 1, 2, 8, 5, 3, 7, 2};
        ForwardList<int> expected_lst4{1, 9, 4, 5, 1, 2, 8, 5, 3, 7, 2};

        auto it1 = original_list.begin();
        for (std::size_t i = 0; i < 3; ++i)
            ++it1;
        original_list.insert_after(it1, 8);
        assertBool(original_list == expected_lst1, __LINE__, __FILE__);

        auto it2 = original_list.begin();
        for (std::size_t i = 0; i < 7; ++i)
            ++it2;
        original_list.insert_after(it2, 2);
        assertBool(original_list == expected_lst2, __LINE__, __FILE__);

        auto it3 = original_list.begin();
        original_list.insert_after(it3, 4);
        assertBool(original_list == expected_lst3, __LINE__, __FILE__);

        auto it4 = original_list.before_begin();
        original_list.insert_after(it4, 1);
        assertBool(original_list == expected_lst4, __LINE__, __FILE__);
    }
};

static InsertTest insertTest;
}  // namespace test
