#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../includes/component.hpp"
#include "../includes/command.hpp"

#include <iostream>

#include <string>

TEST_CASE("Your test case") {
    std::cout << "hello world" << std::endl;
    assert(true);
}

// testing component
TEST_CASE("AndGate") {
    // Register one("one");
    // Register two("two");
    // Register three("three");
    // Register four("four");

    // AndGate test("test");
    // test.AttachInput(&one);
    // test.AttachInput(&two);
    // test.AttachInput(&three);
    // test.AttachInput(&four);

    SECTION("Two Input") {
        SECTION("True True") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(true);

            AndGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

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

            REQUIRE(truefalse.GetState() == true);
        }
    }
}


#endif