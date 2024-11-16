#pragma once
#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>
#include "../Set.h"
#include "CustomAsserts.h"

#include <set>

namespace test {
struct TimeLimitTest {
    TimeLimitTest() {
        Set set;

        auto start = std::chrono::system_clock::now();

        for (std::size_t i = 0; i < 1000000; ++i) {
            set.insert(i);
        }

        auto end = std::chrono::system_clock::now();

        using namespace std::chrono_literals;

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                         end - start)
                  << '\n';

        assertBool(end - start < 1000ms, __LINE__, __FILE__);
    }
};

static TimeLimitTest timeLimitTest;
}  // namespace test
