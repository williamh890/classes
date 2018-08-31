#include "catch.hpp"

#include "../src/quicksort.h"

#include <vector> // vector
#include <algorithm> // is_sorted


std::vector<std::vector<int>> loadTestingDataFrom(const std::string & file) {
    return {{2, 1}};
}

TEST_CASE( "Lists are sorted after sorting", "[quicksort]" ) {
    auto testingLists = loadTestingDataFrom("testing_data.txt");

    for (auto & l : testingLists) {
        quicksort(l);

        REQUIRE(std::is_sorted(l.begin(), l.end()));
    }
}

