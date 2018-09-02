#include "../src/quicksort.h"

#include "catch.hpp"
#include <rapidcheck.h>

#include <vector> // std::vector
#include <algorithm> // std::is_sorted
#include <string> // std::string
#include <iostream>

void print(const std::vector<int> & l);

TEST_CASE("ints are sorted after calling quicksort", "[quicksort]") {
    rc::check("ints are sorted with quicksort",
        [](const std::vector<int> &l0) {
            std::vector<int> l = l0;

            quicksort(l, 0, l.size() - 1);

            auto isSorted = std::is_sorted(l.begin(), l.end());
            REQUIRE(isSorted);
    });
}


TEST_CASE("strs are sorted after calling quicksort", "[quicksort]") {
    rc::check("strings are sorted correctly with quicksort",
        [](const std::vector<std::string> &l0) {
            std::vector<std::string> l = l0;

            quicksort(l, 0, l.size() - 1);

            auto isSorted = std::is_sorted(l.begin(), l.end());
            REQUIRE(isSorted);
    });
}


void print(const std::vector<int> & l) {
    for (auto & v : l) {
        std::cout << v << " ";
    } std::cout << std::endl;
}
