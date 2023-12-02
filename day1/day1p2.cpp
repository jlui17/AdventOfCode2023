/*
--- Part Two ---
Your calculation isn't quite right. It looks like some of the digits are
actually spelled out with letters: one, two, three, four, five, six, seven,
eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last
digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen
In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76.
Adding these together produces 281.

What is the sum of all of the calibration values?
*/

#include <fstream>
#include <iostream>
#include <map>
#include <string>

std::map<std::string, int> wordToNumMap = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

std::string NOT_FOUND = "NOT_FOUND";

std::string getNumAsWord(int i, std::string nextLine) {
    int l = i;
    int r = i + 1;
    std::string numAsWord;
    numAsWord += nextLine[i];

    while (r < nextLine.size() && (r - l) < 5) {
        numAsWord += nextLine[r++];
        if (wordToNumMap.count(numAsWord) > 0) return numAsWord;
    }

    return NOT_FOUND;
}

int getCalibration(std::string nextLine) {
    std::vector<int> v;

    for (int i = 0; i < nextLine.size(); i++) {
        char c = nextLine[i];

        if (std::isdigit(c)) {
            int x = c - '0';
            v.push_back(x);
            continue;
        }

        std::string numAsWord = getNumAsWord(i, nextLine);
        if (numAsWord != NOT_FOUND) {
            v.push_back(wordToNumMap[numAsWord]);
        }
    }

    return v[0] * 10 + v[v.size() - 1];
}

int main() {
    std::fstream file;
    file.open("input.txt", std::ios::in);

    if (!file.is_open()) {
        std::cout << "Couldn't open file";
        return 0;
    }

    std::string nextLine;
    int res = 0;

    while (std::getline(file, nextLine)) {
        int c = getCalibration(nextLine);
        res += c;
    }
    std::cout << res << "\n";

    file.close();
    return 0;
}
