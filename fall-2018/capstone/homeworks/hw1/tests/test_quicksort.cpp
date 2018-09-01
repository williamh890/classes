#include "catch.hpp"

#include "../src/quicksort.h"

#include <vector> // std::vector
#include <algorithm> // std::is_sorted

#include <fstream> // std::ifstream
#include <iostream>
#include <string>
#include <sstream>

const std::string TESTING_DATA_FILE = "tests/testing_data.txt";

std::vector<std::vector<IndexType>> loadTestingDataFrom(const std::string & file) {
    std::ifstream infile(file);

    std::string line = "";
    std::vector<std::vector<IndexType>> testingArrays;

    while (std::getline(infile, line)) {
        IndexType val;
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

void print(std::vector<IndexType> & l) {
    for (auto & v : l) {
        std::cout << v << " ";
    }

    std::cout << std::endl;
}

TEST_CASE("Lists are sorted after sorting", "[quicksort]") {
    auto testingLists = loadTestingDataFrom(TESTING_DATA_FILE);

    for (auto & l : testingLists) {
        quicksort(l, 0, l.size() - 1);
        auto isSorted = std::is_sorted(l.begin(), l.end());

        REQUIRE(isSorted);
    }
}


