#pragma once
#include "../List.h"
#include "CustomAsserts.h"

namespace test {

static std::size_t destructorCallCounter = 0;

struct TestClassForDestructorWothAssignment {
    auto& operator=(const TestClassForDestructorWothAssignment& _) {
        this->~TestClassForDestructorWothAssignment();
        return *this;
    }
    ~TestClassForDestructorWothAssignment() { ++destructorCallCounter; }
};

struct DestructorWithAssignmentTest {
    DestructorWithAssignmentTest() {
        List<TestClassForDestructorWothAssignment> lst1(10);
        List<TestClassForDestructorWothAssignment> lst2(20);

        lst2 = lst1;

        assertGreater(destructorCallCounter, std::size_t(19), __LINE__,
                      __FILE__);
    }
};

static DestructorWithAssignmentTest destructorWithAssignmentTest;
}  // namespace test
