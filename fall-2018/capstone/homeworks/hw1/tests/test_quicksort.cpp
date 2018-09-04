#include "../src/quicksort.h" // qs::quicksort

#include "catch.hpp"
#include <rapidcheck.h> // rc::check

#include <vector> // std::vector
#include <algorithm> // std::is_sorted


TEST_CASE("values are sorted after quicksort") {
    rc::check([](std::vector<int> && l) {
        qs::quicksort(l, 0, l.size() - 1);

        REQUIRE(std::is_sorted(begin(l), end(l)));
    });
}
