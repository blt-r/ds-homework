#pragma once
#include "../ForwardList.h"
#include "CustomAsserts.h"

namespace test {
struct TestClassForMemberAccess {
    auto getVal() -> std::string { return "getVal"; }

    auto getVal() const -> std::string { return "getVal const"; }
};

struct MemberAccessIteratorTest {
    MemberAccessIteratorTest() {
        ForwardList<TestClassForMemberAccess> lst1(10);
        ForwardList<TestClassForMemberAccess>::iterator it1 = lst1.begin();

        using namespace std::string_literals;
        assertEqual(it1->getVal(), "getVal"s, __LINE__, __FILE__);

        ForwardList<TestClassForMemberAccess>::const_iterator const_it1 =
            lst1.begin();
        assertEqual(const_it1->getVal(), "getVal const"s, __LINE__, __FILE__);

        const auto& lst2 = lst1;
        auto it2 = lst2.begin();
        assertEqual(it2->getVal(), "getVal const"s, __LINE__, __FILE__);

        it2 = it1;
        assertEqual(it2->getVal(), "getVal const"s, __LINE__, __FILE__);
        assertEqual((*it2).getVal(), "getVal const"s, __LINE__, __FILE__);
    }
};

static MemberAccessIteratorTest memberAccessIteratorTest;
}  // namespace test
