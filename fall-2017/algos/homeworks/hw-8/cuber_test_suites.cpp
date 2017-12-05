// cuber_test_suites.cpp
// William Horn
// 2 Dec 2017
//
// For CS 311 Fall 2017
// Tests for class Cuber: test suites
// For Assignment 8, Exercise B
// Uses the "Catch" unit-testing framework
// Requires cuber_test_main.cpp, catch.hpp, cuber.h

// Includes for code to be tested
#include "cuber.h"         // For class Cuber
#include "cuber.h"         // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "const and non const cubers",
           "Both const and nonconst cuber objects work." ) {
    Cuber c;
    const Cuber cConst;

    double x = c(1.);
    double y = cConst(1.);

    REQUIRE(x == y);
}


TEST_CASE("wide range of values", "works for a wide range of values") {
    Cuber c;

    auto limit = 200;

    for (int i = 0; i < limit; i += 10) {
        auto mult = i;
        REQUIRE(c(mult) == mult * mult * mult);
        mult = i * -1;
        REQUIRE(c(mult) == mult * mult * mult);
    }
}


TEST_CASE("+/- values", "works for both positive and negative values") {
    Cuber c;

    auto pos = 42;
    auto neg = -42;


    REQUIRE(c(pos) == pos * pos * pos);
    REQUIRE(c(neg) == neg * neg * neg);
}


TEST_CASE("type checks", "works for both floating point and int types") {
    Cuber c;

    float f = 32.3;
    double d = 15.3124887;
    int i = 16;

    REQUIRE(c(f) == f * f * f);
    REQUIRE(c(d) == d * d * d);
    REQUIRE(c(i) == i * i * i);
}


TEST_CASE("char cubing", "does cuber work with cubing characters") {
    Cuber c;

    char x = 'x';

    REQUIRE_FALSE(c(x) == x * x * x);
}






