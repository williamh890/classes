#include "../src/quicksort.h"

#include "catch.hpp"
#include <rapidcheck.h>

#include <vector> // std::vector
#include <algorithm> // std::is_sorted
#include <string> // std::string
#include <iostream>

void print(const std::vector<int> & l);


TEST_CASE("ints are sorted after calling quicksort", "[quicksort]") {
    auto is_sorted_property_test =
        [](std::vector<int> &&l) {
            quicksort(l, 0, l.size() - 1);

            REQUIRE(std::is_sorted(l.begin(), l.end()));
        };

    rc::check(is_sorted_property_test);
}


TEST_CASE("strs are sorted after calling quicksort", "[quicksort]") {
    auto is_sorted_property_test =
        [](std::vector<std::string> &&l) {
            quicksort(l, 0, l.size() - 1);

            REQUIRE(std::is_sorted(l.begin(), l.end()));
        };

    rc::check(is_sorted_property_test);
}


void print(const std::vector<int> & l) {
    for (auto & v : l) {
        std::cout << v << " ";
    } std::cout << std::endl;
}
