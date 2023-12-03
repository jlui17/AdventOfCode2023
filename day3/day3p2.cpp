/*
--- Part Two ---
The engineer finds the missing part and installs it in the engine! As the engine
springs to life, you jump in the closest gondola, finally ready to ascend to the
water source.

You don't seem to be going very fast, though. Maybe something is still wrong?
Fortunately, the gondola has a phone labeled "help", so you pick it up and the
engineer answers.

Before you can explain the situation, she suggests that you look out the window.
There stands the engineer, holding a phone in one hand and waving with the
other. You're going so slowly that you haven't even left the station. You exit
the gondola.

The missing part wasn't the only issue - one of the gears in the engine is
wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its
gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so
that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
In this schematic, there are two gears. The first is in the top left; it has
part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the
lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear
because it is only adjacent to one part number.) Adding up all of the gear
ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?
*/

#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int getPart(int r, int c, string engineLine, set<pair<int, int>> *seen) {
    string rPart;
    string lPart;
    int left = c - 1;
    int right = c;

    while (right < engineLine.length() && isdigit(engineLine[right])) {
        pair<int, int> p(r, right);
        if (seen->count(p)) break;

        rPart += engineLine[right];
        seen->insert(p);
        right++;
    }
    while (left >= 0 && isdigit(engineLine[left])) {
        pair<int, int> p(r, left);
        if (seen->count(p)) break;

        lPart += engineLine[left];
        seen->insert(p);
        left--;
    }

    reverse(lPart.begin(), lPart.end());
    return rPart.length() + lPart.length() == 0 ? 0 : stoi(lPart + rPart);
}

int sumGearRatios(vector<string> engine) {
    int res = 0;
    int R_MAX = engine.size();
    int C_MAX = engine[0].length();

    for (int r = 0; r < R_MAX; r++) {
        set<pair<int, int>> seen;
        for (int c = 0; c < C_MAX; c++) {
            if (engine[r][c] != '*') continue;

            vector<int> adjNums;
            for (int dr = r - 1; dr <= r + 1; dr++) {
                for (int dc = c - 1; dc <= c + 1; dc++) {
                    pair<int, int> p(dr, dc);
                    if ((dr == r && dc == c) || dr < 0 || dr >= R_MAX ||
                        dc < 0 || dc >= C_MAX || !isdigit(engine[dr][dc]) ||
                        seen.count(p))
                        continue;

                    int gr = getPart(dr, dc, engine[dr], &seen);
                    adjNums.push_back(gr);
                }
            }

            if (adjNums.size() != 2) continue;

            int gearRatio = 1;
            for (int gr : adjNums) {
                gearRatio *= gr;
            }
            res += gearRatio;
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

    string nextLine;
    vector<string> engine;

    while (getline(file, nextLine)) {
        engine.push_back(nextLine);
    }

    file.close();

    int res = sumGearRatios(engine);
    cout << res << endl;

    return 0;
}
