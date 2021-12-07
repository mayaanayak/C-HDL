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

            REQUIRE(truetrue.GetState());
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

    SECTION("Multiple Input") {
        SECTION("ttt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(true);

            AndGate ttt("ttt");
            ttt.AttachInput(&one);
            ttt.AttachInput(&two);
            ttt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ttt.GetState());
        }

        SECTION("fff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(false);

            AndGate fff("fff");
            fff.AttachInput(&one);
            fff.AttachInput(&two);
            fff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(fff.GetState());
        }

        SECTION("tft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(true);

            AndGate tft("tft");
            tft.AttachInput(&one);
            tft.AttachInput(&two);
            tft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(tft.GetState());
        }

        SECTION("ftf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(false);

            AndGate ftf("ftf");
            ftf.AttachInput(&one);
            ftf.AttachInput(&two);
            ftf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ftf.GetState());
        }

        SECTION("tff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(false);

            AndGate tff("tff");
            tff.AttachInput(&one);
            tff.AttachInput(&two);
            tff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(tff.GetState());
        }

        SECTION("ftt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(true);

            AndGate ftt("ftt");
            ftt.AttachInput(&one);
            ftt.AttachInput(&two);
            ftt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ftt.GetState());
        }

        SECTION("ttf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(false);

            AndGate ttf("ttf");
            ttf.AttachInput(&one);
            ttf.AttachInput(&two);
            ttf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ttf.GetState());
        }

        SECTION("fft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(true);

            AndGate fft("fft");
            fft.AttachInput(&one);
            fft.AttachInput(&two);
            fft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(fft.GetState());
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

    SECTION("Multiple Input") {
        SECTION("ttt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(true);

            NandGate ttt("ttt");
            ttt.AttachInput(&one);
            ttt.AttachInput(&two);
            ttt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ttt.GetState());
        }

        SECTION("fff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(false);

            NandGate fff("fff");
            fff.AttachInput(&one);
            fff.AttachInput(&two);
            fff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(fff.GetState());
        }

        SECTION("tft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(true);

            NandGate tft("tft");
            tft.AttachInput(&one);
            tft.AttachInput(&two);
            tft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(tft.GetState());
        }

        SECTION("ftf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(false);

            NandGate ftf("ftf");
            ftf.AttachInput(&one);
            ftf.AttachInput(&two);
            ftf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ftf.GetState());
        }

        SECTION("tff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(false);

            NandGate tff("tff");
            tff.AttachInput(&one);
            tff.AttachInput(&two);
            tff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(tff.GetState());
        }

        SECTION("ftt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(true);

            NandGate ftt("ftt");
            ftt.AttachInput(&one);
            ftt.AttachInput(&two);
            ftt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ftt.GetState());
        }

        SECTION("ttf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(false);

            NandGate ttf("ttf");
            ttf.AttachInput(&one);
            ttf.AttachInput(&two);
            ttf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ttf.GetState());
        }

        SECTION("fft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(true);

            NandGate fft("fft");
            fft.AttachInput(&one);
            fft.AttachInput(&two);
            fft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(fft.GetState());
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

    SECTION("Multiple Input") {
        SECTION("ttt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(true);

            OrGate ttt("ttt");
            ttt.AttachInput(&one);
            ttt.AttachInput(&two);
            ttt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ttt.GetState());
        }

        SECTION("fff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(false);

            OrGate fff("fff");
            fff.AttachInput(&one);
            fff.AttachInput(&two);
            fff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(fff.GetState());
        }

        SECTION("tft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(true);

            OrGate tft("tft");
            tft.AttachInput(&one);
            tft.AttachInput(&two);
            tft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(tft.GetState());
        }

        SECTION("ftf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(false);

            OrGate ftf("ftf");
            ftf.AttachInput(&one);
            ftf.AttachInput(&two);
            ftf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ftf.GetState());
        }

        SECTION("tff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(false);

            OrGate tff("tff");
            tff.AttachInput(&one);
            tff.AttachInput(&two);
            tff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(tff.GetState());
        }

        SECTION("ftt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(true);

            OrGate ftt("ftt");
            ftt.AttachInput(&one);
            ftt.AttachInput(&two);
            ftt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ftt.GetState());
        }

        SECTION("ttf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(false);

            OrGate ttf("ttf");
            ttf.AttachInput(&one);
            ttf.AttachInput(&two);
            ttf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ttf.GetState());
        }

        SECTION("fft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(true);

            OrGate fft("fft");
            fft.AttachInput(&one);
            fft.AttachInput(&two);
            fft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(fft.GetState());
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

    SECTION("Multiple Input") {
        SECTION("ttt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(true);

            NorGate ttt("ttt");
            ttt.AttachInput(&one);
            ttt.AttachInput(&two);
            ttt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ttt.GetState());
        }

        SECTION("fff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(false);

            NorGate fff("fff");
            fff.AttachInput(&one);
            fff.AttachInput(&two);
            fff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(fff.GetState());
        }

        SECTION("tft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(true);

            NorGate tft("tft");
            tft.AttachInput(&one);
            tft.AttachInput(&two);
            tft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(tft.GetState());
        }

        SECTION("ftf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(false);

            NorGate ftf("ftf");
            ftf.AttachInput(&one);
            ftf.AttachInput(&two);
            ftf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ftf.GetState());
        }

        SECTION("tff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(false);

            NorGate tff("tff");
            tff.AttachInput(&one);
            tff.AttachInput(&two);
            tff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(tff.GetState());
        }

        SECTION("ftt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(true);

            NorGate ftt("ftt");
            ftt.AttachInput(&one);
            ftt.AttachInput(&two);
            ftt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ftt.GetState());
        }

        SECTION("ttf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(false);

            NorGate ttf("ttf");
            ttf.AttachInput(&one);
            ttf.AttachInput(&two);
            ttf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ttf.GetState());
        }

        SECTION("fft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(true);

            NorGate fft("fft");
            fft.AttachInput(&one);
            fft.AttachInput(&two);
            fft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(fft.GetState());
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

    SECTION("Multiple Input") {
        SECTION("ttt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(true);

            XorGate ttt("ttt");
            ttt.AttachInput(&one);
            ttt.AttachInput(&two);
            ttt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ttt.GetState());
        }

        SECTION("fff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(false);

            XorGate fff("fff");
            fff.AttachInput(&one);
            fff.AttachInput(&two);
            fff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(fff.GetState());
        }

        SECTION("tft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(true);

            XorGate tft("tft");
            tft.AttachInput(&one);
            tft.AttachInput(&two);
            tft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(tft.GetState());
        }

        SECTION("ftf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(false);

            XorGate ftf("ftf");
            ftf.AttachInput(&one);
            ftf.AttachInput(&two);
            ftf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(ftf.GetState());
        }

        SECTION("tff") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(false);
            three.SetState(false);

            XorGate tff("tff");
            tff.AttachInput(&one);
            tff.AttachInput(&two);
            tff.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(tff.GetState());
        }

        SECTION("ftt") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(true);
            three.SetState(true);

            XorGate ftt("ftt");
            ftt.AttachInput(&one);
            ftt.AttachInput(&two);
            ftt.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ftt.GetState());
        }

        SECTION("ttf") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(true);
            two.SetState(true);
            three.SetState(false);

            XorGate ttf("ttf");
            ttf.AttachInput(&one);
            ttf.AttachInput(&two);
            ttf.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE_FALSE(ttf.GetState());
        }

        SECTION("fft") {
            Register one("one");
            Register two("two");
            Register three("three");

            one.SetState(false);
            two.SetState(false);
            three.SetState(true);

            XorGate fft("fft");
            fft.AttachInput(&one);
            fft.AttachInput(&two);
            fft.AttachInput(&three);

            one.Evaluate();
            two.Evaluate();
            three.Evaluate();

            REQUIRE(fft.GetState());
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