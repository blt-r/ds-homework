#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

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
        // of List must be called.
        {
            List<TestClassForDestructor> lst(10, destructorTestClassObj);

            for (std::size_t i = 0; i < 20; ++i)
                lst.push_front(destructorTestClassObj);
        }
        assertEqual(destructorCallCounter, std::size_t(30), __LINE__, __FILE__);

        destructorCallCounter = 0;
        {
            List<TestClassForDestructor> lst(10, destructorTestClassObj);

            for (std::size_t i = 0; i < 5; ++i)
                lst.pop_front();

            assertEqual(destructorCallCounter, std::size_t(5), __LINE__,
                        __FILE__);
        }
        assertEqual(destructorCallCounter, std::size_t(10), __LINE__, __FILE__);
    }
};

static DestructorCallTest destructorCallTest;
}  // namespace test
