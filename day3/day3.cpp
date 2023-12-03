/*
--- Day 3: Gear Ratios ---
You and the Elf eventually reach a gondola lift station; he says the gondola
lift will take you up to the water source, but this is as far as he can bring
you. You go inside.

It doesn't take long to find the gondolas, but there seems to be a problem:
they're not moving.

"Aaah!"

You turn around to see a slightly-greasy Elf with a wrench and a look of
surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working
right now; it'll still be a while before I can fix it." You offer to help.

The engineer explains that an engine part seems to be missing from the engine,
but nobody can figure out which one. If you can add up all the part numbers in
the engine schematic, it should be easy to work out which part is missing.

The engine schematic (your puzzle input) consists of a visual representation of
the engine. There are lots of numbers and symbols you don't really understand,
but apparently any number adjacent to a symbol, even diagonally, is a "part
number" and should be included in your sum. (Periods (.) do not count as a
symbol.)

Here is an example engine schematic:

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
In this schematic, two numbers are not part numbers because they are not
adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number
is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all of
the part numbers in the engine schematic?
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
    set<pair<int, int>> seen;
    int res = 0;
    int R_MAX = engine.size();
    int C_MAX = engine[0].length();

    for (int r = 0; r < R_MAX; r++) {
        for (int c = 0; c < C_MAX; c++) {
            if (engine[r][c] == '.' || isdigit(engine[r][c])) continue;

            for (int dr = r - 1; dr <= r + 1; dr++) {
                for (int dc = c - 1; dc <= c + 1; dc++) {
                    pair<int, int> p(dr, dc);
                    if ((dr == r && dc == c) || dr < 0 || dr >= R_MAX ||
                        dc < 0 || dc >= C_MAX || !isdigit(engine[dr][dc]) ||
                        seen.count(p))
                        continue;

                    int part = getPart(dr, dc, engine[dr], &seen);
                    res += part;
                }
            }
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
