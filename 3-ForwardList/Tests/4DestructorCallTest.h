#pragma once
#include "../ForwardList.h"
#include "CustomAsserts.h"

namespace test {
struct TestClassForDestructor {
    std::size_t* destructorCallCounterPtr;

    TestClassForDestructor() : destructorCallCounterPtr(nullptr) {}

    TestClassForDestructor(std::size_t* destructorCallCounterPtr)
        : destructorCallCounterPtr(destructorCallCounterPtr) {}

    ~TestClassForDestructor() {
        if (destructorCallCounterPtr)
            ++(*destructorCallCounterPtr);
    }
};

struct DestructorCallTest {
    DestructorCallTest() {
        std::size_t destructorCallCounter = 0;
        TestClassForDestructor destructorTestClassObj(&destructorCallCounter);

        // The code below is written between 2 brackets because after this
        // brackets the object `lst` must be destroyed and hence the destructor
        // of ForwardList must be called.
        {
            ForwardList<TestClassForDestructor> lst(10, destructorTestClassObj);

            for (std::size_t i = 0; i < 20; ++i)
                lst.push_front(destructorTestClassObj);
        }
        assertEqual(destructorCallCounter, 30u, __LINE__, __FILE__);

        destructorCallCounter = 0;
        {
            ForwardList<TestClassForDestructor> lst(10, destructorTestClassObj);

            for (std::size_t i = 0; i < 5; ++i)
                lst.pop_front();

            assertEqual(destructorCallCounter, 5u, __LINE__, __FILE__);
        }
        assertEqual(destructorCallCounter, 10u, __LINE__, __FILE__);
    }
};

static DestructorCallTest destructorCallTest;
}  // namespace test
