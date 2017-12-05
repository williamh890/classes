// wordcount.cpp
// William Horn
// Created: Dec 4, 2017
// cs311 a8, Exercise A

#include<iostream>
using std::cout;
using std::endl;
using std::cin;
#include<string>
using std::string;
#include<fstream>
using std::ifstream;
#include<vector>
using std::vector;
#include<map>
using std::map;


vector<string> parseForWords(string s) {
    vector<string> words;

    string curr = "";
    for (auto & c : s) {
        // Don't start word on whitespace
        if (curr == "" && isspace(c)) {
            continue;
        }
        // End of a word
        else if (isspace(c)) {
            words.push_back(curr);
            curr = "";
        }
        // Add to word
        else {
            curr += c;
        }
    }

    return words;
}


void printMap(const map<string, int> & m) {
    string separator(40, '-');

    cout << separator << endl;

    auto end = m.end();
    for (auto it = m.begin(); it != end; ++it) {
        cout << it->first << " => " << it->second << endl;
    }

    cout << separator << endl;
}


void uniqueWords(vector<string> & lines) {
    map<std::string, int> counts;

    for (auto & line : lines) {
        auto words = parseForWords(line);

        for(auto & word : words) {
            if (counts.count(word) == 0) {
                counts[word] = 1;
                continue;
            }

            counts[word] += 1;
        }
    }

    printMap(counts);
}


int main() {
    while (true) {
        cout << "Enter a text file (nothing to exit): ";

        string filePath;
        getline(cin, filePath);

        if (filePath == "") {
            break;
        }

        ifstream wordFile(filePath);

        if (!wordFile.is_open()) {
            cout << "error opening file...\n" << endl;
            continue;
        }

        cout << "File '"  << filePath << "' has been opened\n" << endl;
        vector<string> lines;
        string line;

        while (getline(wordFile, line)) {
            lines.push_back(line);
        }

        try {
            uniqueWords(lines);
        } catch(...) {
            cout << "Error processing file..." << endl;
        }
    }

    return 0;
}


