#pragma once
#include <deque>
#include <string>
#include <vector>
#include "../HeapFunctions.h"
#include "CheckHeap.h"
#include "CustomAsserts.h"

namespace test {
struct TestClassForComparator {
    int first;
    int second;
};

struct ComparatorTest {
    ComparatorTest() {
        auto isGreater = [](int a, int b) { return a > b; };

        std::vector<int> vec{5, 70, 99, 52, 24, 59, 45, 72, 1, 68};
        makeHeap(vec.begin(), vec.end(), isGreater);
        assertBool(isHeap(vec.begin(), vec.end(), isGreater), __LINE__,
                   __FILE__);

        for (std::size_t i = 0; i < vec.size() - 1; ++i) {
            popHeap(vec.begin(), vec.end() - i, isGreater);
            assertBool(isHeap(vec.begin(), vec.end() - i - 1, isGreater),
                       __LINE__, __FILE__);
            auto heapEnd = vec.end() - i;
            assertBool(
                *(heapEnd - 1) == *std::min_element(vec.begin(), heapEnd),
                __LINE__, __FILE__);
        }

        auto isLessTestObj = [](TestClassForComparator obj1,
                                TestClassForComparator obj2) {
            return obj1.first < obj2.first;
        };
        std::deque<TestClassForComparator> deq{{33, 1},  {65, 91}, {93, 85},
                                               {83, 61}, {59, 65}, {18, 3},
                                               {80, 63}, {26, 64}, {87, 15}};
        std::deque<TestClassForComparator> dequeHeap;
        for (const auto& value : deq) {
            dequeHeap.push_back(value);
            pushHeap(dequeHeap.begin(), dequeHeap.end(), isLessTestObj);
            assertBool(
                isHeap(dequeHeap.begin(), dequeHeap.end(), isLessTestObj),
                __LINE__, __FILE__);
        }
    }
};

static ComparatorTest comparatorTest;
}  // namespace test
