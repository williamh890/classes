#include "catch.hpp"

#include "../src/quicksort.h"

#include <vector> // std::vector
#include <algorithm> // std::is_sorted
#include <cassert> // assert

#include <fstream> // std::ifstream
#include <string> // std::string
#include <sstream> // std::istringstream


const std::string TESTING_DATA_FILE = "tests/testing_data.txt";
using TestValueType = int;


std::vector<std::vector<TestValueType>>
loadTestingDataFrom(const std::string & file);


TEST_CASE("Lists are sorted after sorting", "[quicksort]") {
    auto testingLists = loadTestingDataFrom(TESTING_DATA_FILE);

    assert(
        testingLists.size() > 0 &&
        "Testing needs to be from root directory to load testing data properly"
    );

    for (auto & l : testingLists) {
        quicksort(l, 0, l.size() - 1);
        auto isSorted = std::is_sorted(l.begin(), l.end());

        REQUIRE(isSorted);
    }
}


std::vector<std::vector<TestValueType>>
loadTestingDataFrom(const std::string & file) {
    std::ifstream infile(file);

    std::string line = "";
    std::vector<std::vector<TestValueType>> testingArrays;

    while (std::getline(infile, line)) {
        TestValueType val;
        std::vector<IndexType> vals = {};
        std::istringstream ss(line);

        while(true) {
            ss >> val;
            if (!ss) break;

            vals.push_back(val);
        }

        testingArrays.push_back(vals);
    }

    return testingArrays;
}
