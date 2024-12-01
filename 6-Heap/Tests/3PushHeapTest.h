#pragma once
#include <deque>
#include <string>
#include <vector>
#include "../HeapFunctions.h"
#include "CheckHeap.h"
#include "CustomAsserts.h"

namespace test {
struct PushHeapTest {
    PushHeapTest() {
        std::vector<int> vec{5, 70, 99, 52, 24, 59, 45, 72, 1, 68};
        std::vector<int> vecHeap;
        for (const int value : vec) {
            vecHeap.push_back(value);
            pushHeap(vecHeap.begin(), vecHeap.end());
            assertBool(isHeap(vecHeap.begin(), vecHeap.end()), __LINE__,
                       __FILE__);
        }

        std::deque<double> deq{33, 1, 65, 91, 93, 85, 83, 61, 59, 65,
                               18, 3, 80, 63, 26, 64, 87, 15, 91, 90};
        std::deque<double> dequeHeap;
        for (const double value : deq) {
            dequeHeap.push_back(value);
            pushHeap(dequeHeap.begin(), dequeHeap.end());
            assertBool(isHeap(dequeHeap.begin(), dequeHeap.end()), __LINE__,
                       __FILE__);
        }

        std::string str{
            "Charles ate the french fries knowing they would be his last meal."
            "While on the first date he accidentally hit his head on the beam."
            "Art doesn't have to be intentional."
            "He always wore his sunglasses at night."};
        std::string strHeap;
        for (const char value : str) {
            strHeap.push_back(value);
            pushHeap(strHeap.begin(), strHeap.end());
            assertBool(isHeap(strHeap.begin(), strHeap.end()), __LINE__,
                       __FILE__);
        }
    }
};

static PushHeapTest pushHeapTest;
}  // namespace test
