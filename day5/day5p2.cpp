/*
--- Part Two ---
Everyone will starve if you only plant such a small number of seeds. Re-reading
the almanac, it looks like the seeds: line actually describes ranges of seed
numbers.

The values on the initial seeds: line come in pairs. Within each pair, the first
value is the start of the range and the second value is the length of the range.
So, in the first line of the example above:

seeds: 79 14 55 13
This line describes two ranges of seed numbers to be planted in the garden. The
first range starts with seed number 79 and contains 14 values: 79, 80, ...,
91, 92. The second range starts with seed number 55 and contains 13 values: 55,
56, ..., 66, 67.

Now, rather than considering four seed numbers, you need to consider a total of
27 seed numbers.

In the above example, the lowest location number can be obtained from seed
number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77,
temperature 45, humidity 46, and location 46. So, the lowest location number
is 46.

Consider all of the initial seed numbers listed in the ranges on the first line
of the almanac. What is the lowest location number that corresponds to any of
the initial seed numbers?
*/

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

vector<string> split(string s, char del) {
    vector<string> res;
    string str;
    stringstream ss(s);

    while (getline(ss, str, del)) res.push_back(str);

    return res;
}

void getNextSection(fstream &file, vector<string> *dest) {
    string nextLine;
    int res = 0;
    while (getline(file, nextLine)) {
        if (nextLine == "") return;
        dest->push_back(nextLine);
    }
}

vector<pair<long, long>> getSeeds(vector<string> seeds) {
    vector<pair<long, long>> res;
    vector<string> first = split(seeds[0], ' ');
    for (int i = 1; i < first.size(); i += 2) {
        long start = stol(first[i]);
        long end = stol(first[i + 1]) + start;
        pair<long, long> p(start, end);
        res.push_back(p);
    }

    return res;
}

// <dest, start, length>
vector<tuple<long, long, long>> getMap(vector<string> encodedMap) {
    vector<tuple<long, long, long>> res;
    for (int i = 1; i < encodedMap.size(); i++) {
        vector<string> line = split(encodedMap[i], ' ');
        tuple<long, long, long> t{stol(line[0]), stol(line[1]), stol(line[2])};
        res.push_back(t);
    }
    return res;
}

vector<pair<long, long>> convertSeeds(vector<pair<long, long>> seeds,
                                      vector<tuple<long, long, long>> map) {
    vector<pair<long, long>> res;
    while (seeds.size()) {
        pair<long, long> seed = seeds.back();
        seeds.pop_back();

        long start = seed.first;
        long end = seed.second;
        bool matched = false;
        for (auto range : map) {
            long dest = get<0>(range);
            long src = get<1>(range);
            long len = get<2>(range);

            long os = max(start, src);
            long oe = min(end, src + len);
            if (os < oe) {
                pair<long, long> p(os - src + dest, oe - src + dest);
                res.push_back(p);

                if (os > start) {
                    pair<long, long> temp(start, os);
                    seeds.push_back(temp);
                }
                if (end > oe) {
                    pair<long, long> temp(oe, end);
                    seeds.push_back(temp);
                }
                matched = true;
                break;
            }
        }
        if (!matched) {
            pair<long, long> temp(start, end);
            res.push_back(temp);
        }
    }

    return res;
}

int main() {
    fstream file;
    file.open("input.txt", ios::in);

    if (!file.is_open()) {
        std::cout << "Couldn't open file";
        return 0;
    }

    vector<string> seedsInput;
    vector<string> seedToSoil;
    vector<string> soilToFertilizer;
    vector<string> fertilizerToWater;
    vector<string> waterToLight;
    vector<string> lightToTemperature;
    vector<string> temperatureToHumidity;
    vector<string> humidityToLocation;
    getNextSection(file, &seedsInput);
    getNextSection(file, &seedToSoil);
    getNextSection(file, &soilToFertilizer);
    getNextSection(file, &fertilizerToWater);
    getNextSection(file, &waterToLight);
    getNextSection(file, &lightToTemperature);
    getNextSection(file, &temperatureToHumidity);
    getNextSection(file, &humidityToLocation);

    vector<pair<long, long>> seeds = getSeeds(seedsInput);
    vector<tuple<long, long, long>> seedToSoilMap = getMap(seedToSoil);
    vector<tuple<long, long, long>> soilToFertilizerMap =
        getMap(soilToFertilizer);
    vector<tuple<long, long, long>> fertilizerToWaterMap =
        getMap(fertilizerToWater);
    vector<tuple<long, long, long>> waterToLightMap = getMap(waterToLight);
    vector<tuple<long, long, long>> lightToTemperatureMap =
        getMap(lightToTemperature);
    vector<tuple<long, long, long>> temperatureToHumidityMap =
        getMap(temperatureToHumidity);
    vector<tuple<long, long, long>> humidityToLocationMap =
        getMap(humidityToLocation);
    vector<vector<tuple<long, long, long>>> allMaps{
        seedToSoilMap,        soilToFertilizerMap,   fertilizerToWaterMap,
        waterToLightMap,      lightToTemperatureMap, temperatureToHumidityMap,
        humidityToLocationMap};

    for (auto map : allMaps) {
        seeds = convertSeeds(seeds, map);
    }
    long minLoc = numeric_limits<long>::max();
    for (auto t : seeds) {
        minLoc = min(minLoc, t.first);
    }
    cout << minLoc << endl;

    file.close();
    return 0;
}
