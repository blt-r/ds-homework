#pragma once
#include <deque>
#include <string>
#include <vector>
#include "../HeapFunctions.h"
#include "CheckHeap.h"
#include "CustomAsserts.h"

namespace test {
struct BasicConstructorsTest {
    BasicConstructorsTest() {
        std::vector<int> emptyVec;
        makeHeap(emptyVec.begin(), emptyVec.end());
        assertBool(isHeap(emptyVec.begin(), emptyVec.end()), __LINE__,
                   __FILE__);

        std::vector<int> vec{5, 70, 99, 52, 24, 59, 45, 72, 1, 68};
        makeHeap(vec.begin(), vec.end());
        assertBool(isHeap(vec.begin(), vec.end()), __LINE__, __FILE__);

        std::deque<int> deq{33, 1, 65, 91, 93, 85, 83, 61, 59, 65,
                            18, 3, 80, 63, 26, 64, 87, 15, 91, 90};
        makeHeap(deq.begin(), deq.end());
        assertBool(isHeap(deq.begin(), deq.end()), __LINE__, __FILE__);

        std::string str{
            "Charles ate the french fries knowing they would be his last meal."
            "While on the first date he accidentally hit his head on the beam."
            "Art doesn't have to be intentional."
            "He always wore his sunglasses at night."};
        makeHeap(str.begin(), str.end());
        assertBool(isHeap(str.begin(), str.end()), __LINE__, __FILE__);
    }
};

static BasicConstructorsTest basicConstructorsTest;
}  // namespace test
