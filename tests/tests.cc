#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

#include "../includes/component.hpp"
#include "../includes/command.hpp"

// TEST_CASE("Your test case") {
//     std::cout << "hello world" << std::endl;
//     assert(true);
// }

// testing component
TEST_CASE("AndGate") {
    SECTION("Two Input") {
        SECTION("True True") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(true);

            AndGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

            truetrue.Evaluate();

            REQUIRE(truetrue.GetState() == true);
        }

        SECTION("True False") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(false);

            AndGate truefalse("truefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            truefalse.Evaluate();

            REQUIRE(truefalse.GetState() == false);
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            AndGate truefalse("falsefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            truefalse.Evaluate();

            REQUIRE(truefalse.GetState() == false);
        }
    }
}
