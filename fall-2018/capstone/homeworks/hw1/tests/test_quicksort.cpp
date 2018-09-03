#include "../src/quicksort.h" // qs::quicksort

#include "catch.hpp"
#include <rapidcheck.h> // rc::check

#include <vector> // std::vector
#include <algorithm> // std::is_sorted
#include <string> // std::string


TEST_CASE("ints are sorted after calling quicksort", "[quicksort]") {
    auto is_sorted_property_test = [](std::vector<int> && l) {
        qs::quicksort(l, 0, l.size() - 1);

        REQUIRE(std::is_sorted(l.begin(), l.end()));
    };

    rc::check(is_sorted_property_test);
}
