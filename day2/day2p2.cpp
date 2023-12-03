/*
--- Part Two ---
The Elf says they've stopped producing snow because they aren't getting any
water! He isn't sure why the water stopped; however, he can show you how to get
to the water source to check it out for yourself. It's just up ahead!

As you continue your walk, the Elf poses a second question: in each game you
played, what is the fewest number of cubes of each color that could have been in
the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
In game 1, the game could have been played with as few as 4 red, 2 green, and 6
blue cubes. If any color had even one fewer cube, the game would have been
impossible. Game 2 could have been played with a minimum of 1 red, 3 green, and
4 blue cubes. Game 3 must have been played with at least 20 red, 13 green, and 6
blue cubes. Game 4 required at least 14 red, 3 green, and 15 blue cubes. Game 5
needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag. The power of a
set of cubes is equal to the numbers of red, green, and blue cubes multiplied
together. The power of the minimum set of cubes in game 1 is 48. In games 2-5 it
was 12, 1560, 630, and 36, respectively. Adding up these five powers produces
the sum 2286.

For each game, find the minimum set of cubes that must have been present. What
is the sum of the power of these sets?
*/

#include <fstream>
#include <iostream>
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

pair<string, int> getColorAndAmount(string picks) {
    string amount, color;

    for (char c : picks) {
        if (c == ' ') continue;
        if (isdigit(c))
            amount += c;
        else
            color += c;
    }

    pair<string, int> res(color, stoi(amount));
    return res;
}

// red, green, blue
tuple<int, int, int> getRGB(string hand) {
    vector<string> picks = split(hand, ',');
    int green = 0;
    int red = 0;
    int blue = 0;

    for (string p : picks) {
        pair<string, int> combo = getColorAndAmount(p);
        string color = combo.first;
        int amount = combo.second;

        if (color == "green") {
            green = amount;
        } else if (color == "red") {
            red = amount;
        } else {  // blue
            blue = amount;
        }
    }

    tuple<int, int, int> res(red, green, blue);
    return res;
}

int doGetPowerSet(string game) {
    vector<string> hands = split(game, ';');
    int minRed, minGreen, minBlue = 0;

    for (string hand : hands) {
        tuple<int, int, int> rgb = getRGB(hand);
        minRed = max(minRed, get<0>(rgb));
        minGreen = max(minGreen, get<1>(rgb));
        minBlue = max(minBlue, get<2>(rgb));
    }

    return minRed * minGreen * minBlue;
}

int getPowerSet(string nextGame) {
    vector<string> g = split(nextGame, ':');
    string title = g[0];
    string game = g[1];

    return doGetPowerSet(game);
}

int main() {
    fstream file;
    file.open("input.txt", ios::in);

    if (!file.is_open()) {
        std::cout << "Couldn't open file";
        return 0;
    }

    string nextGame;
    int res = 0;

    while (getline(file, nextGame)) {
        int ps = getPowerSet(nextGame);
        res += ps;
    }

    std::cout << res << "\n";

    file.close();
    return 0;
}
