#include "Set.h"

#include "Tests/1BasicConstructorsTest.h"
#include "Tests/2InsertContainsTest.h"
#include "Tests/3EraseValueTest.h"
#include "Tests/4InitializerListTest.h"
#include "Tests/5CopyConstructorTest.h"
#include "Tests/6AssignmentOperatorTest.h"
#include "Tests/7IteratorTest.h"
#include "Tests/8IteratorStlCompatibilityTest.h"
#include "Tests/9FindTest.h"

#include "Tests/10UpperAndLowerBoundsTest.h"
#include "Tests/11EraseIteratorTest.h"

// Disable sanitizers and eneable optimizations for this
// #include "Tests/12TimeLimitTest.h"

#include <iostream>

auto main() -> int {
    std::cout << "All tests have passed :3\n";
}
