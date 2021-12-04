#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../includes/component.hpp"
#include "../includes/command.hpp"

#include <iostream>

TEST_CASE("Your test case") {
    std::cout << "hello world" << std::endl;
    assert(true);
}

#endif