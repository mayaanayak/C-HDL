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

            one.Evaluate();
            two.Evaluate();

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

            one.Evaluate();
            two.Evaluate();

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

            one.Evaluate();
            two.Evaluate();

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

            NandGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE_FALSE(truetrue.GetState());
        }

        SECTION("True False") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(false);

            NandGate truefalse("truefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE(truefalse.GetState());
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            NandGate truefalse("falsefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

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

            one.Evaluate();
            two.Evaluate();

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

            one.Evaluate();
            two.Evaluate();

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

            one.Evaluate();
            two.Evaluate();

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

            NorGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE_FALSE(truetrue.GetState());
        }

        SECTION("True False") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(false);

            NorGate truefalse("truefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE_FALSE(truefalse.GetState());
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            NorGate falsefalse("falsefalse");
            falsefalse.AttachInput(&one);
            falsefalse.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE(falsefalse.GetState());
        }
    }
}

// XorGate
TEST_CASE("XorGate") {
    SECTION("Two Input") {
        SECTION("True True") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(true);

            XorGate truetrue("truetrue");
            truetrue.AttachInput(&one);
            truetrue.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE_FALSE(truetrue.GetState());
        }

        SECTION("True False") {
            Register one("one");
            Register two("two");

            one.SetState(true);
            two.SetState(false);

            XorGate truefalse("truefalse");
            truefalse.AttachInput(&one);
            truefalse.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE(truefalse.GetState());
        }

        SECTION("False False") {
            Register one("one");
            Register two("two");

            one.SetState(false);
            two.SetState(false);

            XorGate falsefalse("falsefalse");
            falsefalse.AttachInput(&one);
            falsefalse.AttachInput(&two);

            one.Evaluate();
            two.Evaluate();

            REQUIRE_FALSE(falsefalse.GetState());
        }
    }
}

// NotGate
TEST_CASE("NotGate") {
    SECTION("One Input") {
        SECTION("True") {
            Register one("one");

            one.SetState(true);

            NotGate truetrue("truetrue");
            truetrue.AttachInput(&one);

            one.Evaluate();

            REQUIRE_FALSE(truetrue.GetState());
        }

        SECTION("False") {
            Register one("one");

            one.SetState(false);

            NotGate falsefalse("falsefalse");
            falsefalse.AttachInput(&one);

            one.Evaluate();

            REQUIRE(falsefalse.GetState());
        }    
    }
}