#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

#include "../includes/component.hpp"
#include "../includes/command.hpp"

TEST_CASE("Your test case") {
    assert(true);
}

// AndGate
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

            REQUIRE_FALSE(truefalse.GetState());
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            AndGate falsefalse("falsefalse");
            falsefalse.AttachInput(&one);
            falsefalse.AttachInput(&two);

            falsefalse.Evaluate();

            REQUIRE_FALSE(falsefalse.GetState());
        }
    }
}

// NandGate
TEST_CASE("NandGate") {
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

            REQUIRE_FALSE(truetrue.GetState());
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

            REQUIRE(truefalse.GetState());
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

            REQUIRE(truefalse.GetState());
        }
    }
}


// OrGate
TEST_CASE("OrGate") {
    SECTION("Two Input") {
        SECTION("True True") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(true);

            OrGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

            truetrue.Evaluate();

            REQUIRE(truetrue.GetState());
        }

        SECTION("True False") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(false);

            OrGate truefalse("truefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            truefalse.Evaluate();

            REQUIRE(truefalse.GetState());
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            OrGate falsefalse("falsefalse");
            falsefalse.AttachInput(&one);
            falsefalse.AttachInput(&two);

            falsefalse.Evaluate();

            REQUIRE_FALSE(falsefalse.GetState());
        }
    }
}

// NorGate
TEST_CASE("NorGate") {
    SECTION("Two Input") {
        SECTION("True True") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(true);

            OrGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

            truetrue.Evaluate();

            REQUIRE_FALSE(truetrue.GetState());
        }

        SECTION("True False") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(false);

            OrGate truefalse("truefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            truefalse.Evaluate();

            REQUIRE_FALSE(truefalse.GetState());
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            OrGate falsefalse("falsefalse");
            falsefalse.AttachInput(&one);
            falsefalse.AttachInput(&two);

            falsefalse.Evaluate();

            REQUIRE(falsefalse.GetState());
        }
    }
}

