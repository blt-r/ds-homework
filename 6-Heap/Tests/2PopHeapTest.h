#pragma once
#include <deque>
#include <string>
#include <vector>
#include "../HeapFunctions.h"
#include "CheckHeap.h"
#include "CustomAsserts.h"

namespace test {
struct PopHeapTest {
    PopHeapTest() {
        std::vector<int> vec{5, 70, 99, 52, 24, 59, 45, 72, 1, 68};
        makeHeap(vec.begin(), vec.end());
        popHeap(vec.begin(), vec.end());
        assertBool(isHeap(vec.begin(), vec.end() - 1), __LINE__, __FILE__);
        assertBool(vec.back() == *std::max_element(vec.begin(), vec.end()),
                   __LINE__, __FILE__);

        std::string str{
            "Charles ate the french fries knowing they would be his last meal."
            "While on the first date he accidentally hit his head on the beam."
            "Art doesn't have to be intentional."
            "He always wore his sunglasses at night."};
        makeHeap(str.begin(), str.end());
        popHeap(str.begin(), str.end());
        assertBool(isHeap(str.begin(), str.end() - 1), __LINE__, __FILE__);
        assertBool(str.back() == *std::max_element(str.begin(), str.end()),
                   __LINE__, __FILE__);

        std::deque<double> deq{33, 1, 65, 91, 93, 85, 83, 61, 59, 65,
                               18, 3, 80, 63, 26, 64, 87, 15, 91, 90};
        makeHeap(deq.begin(), deq.end());

        for (std::size_t i = 0; i < deq.size() - 1; ++i) {
            popHeap(deq.begin(), deq.end() - i);
            assertBool(isHeap(deq.begin(), deq.end() - i - 1), __LINE__,
                       __FILE__);
            auto heapEnd = deq.end() - i;
            assertBool(
                *(heapEnd - 1) == *std::max_element(deq.begin(), heapEnd),
                __LINE__, __FILE__);
        }
    }
};

static PopHeapTest popHeapTest;
}  // namespace test
