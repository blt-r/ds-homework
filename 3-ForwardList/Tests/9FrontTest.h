#pragma once
#include "../ForwardList.h"
#include "CustomAsserts.h"

namespace test {
struct TestClassForFront {
    std::string getVal() { return "getVal"; }

    std::string getVal() const { return "getVal const"; }
};

struct FrontTest {
    FrontTest() {
        ForwardList<TestClassForFront> lst1(10);
        const auto& lst2 = lst1;

        using namespace std::string_literals;
        assertEqual(lst1.front().getVal(), "getVal"s, __LINE__, __FILE__);
        assertEqual(lst2.front().getVal(), "getVal const"s, __LINE__, __FILE__);
    }
};

static FrontTest frontTest;
}  // namespace test
