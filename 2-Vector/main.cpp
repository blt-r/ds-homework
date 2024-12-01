#include <iostream>

#include "Vector.h"

#include "Tests/1BasicConstructorsTest.h"
#include "Tests/2InitializerListConstructorTest.h"
#include "Tests/3PushBackTest.h"
#include "Tests/4PopBackTest.h"
#include "Tests/5ClearTest.h"
#include "Tests/6CopyConstructorTest.h"
#include "Tests/7AssignmentOperatorTest.h"
#include "Tests/8AccessFunctionsTest.h"
#include "Tests/9ReserveAndShrinkToFitTest.h"

#include "Tests/10SwapTest.h"
#include "Tests/11SubscriptOperatorTest.h"
#include "Tests/12DestructorCallTest.h"
#include "Tests/13EmplaceBackTest.h"
#include "Tests/14ClassWithoutDefaultConstructorTest.h"
#include "Tests/15ClassWithoutCopyConstructorTest.h"
#include "Tests/16MoveConstructorAndMoveAssignmentOperatorTest.h"

auto main() -> int {
    std::cout << "All tests have passed :3\n";
}
