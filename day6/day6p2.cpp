/*
--- Part Two ---
As the race is about to start, you realize the piece of paper with race times
and record distances you got earlier actually just has very bad kerning. There's
really only one race - ignore the spaces between the numbers on each line.

So, the example from before:

Time:      7  15   30
Distance:  9  40  200
...now instead means this:

Time:      71530
Distance:  940200
Now, you have to figure out how many ways there are to win this single race. In
this example, the race lasts for 71530 milliseconds and the record distance you
need to beat is 940200 millimeters. You could hold the button anywhere from 14
to 71516 milliseconds and beat the record, a total of 71503 ways!

How many ways can you beat the record in this one much longer race?
*/

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

long getNum(string input) {
    string n = "";
    for (char c : input) {
        if (isdigit(c)) {
            n += c;
        }
    }
    return stol(n);
}

long calcNumWaysToWin(long time, long distance) {
    long res = 0;

    for (long speed = 1; speed < time; speed++) {
        long timeRemaining = time - speed;
        if (speed * timeRemaining >= distance) res++;
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

    string timeInput;
    string distanceInput;
    getline(file, timeInput);
    getline(file, distanceInput);

    long time = getNum(timeInput);
    long distance = getNum(distanceInput);

    long res = calcNumWaysToWin(time, distance);

    cout << res << endl;

    file.close();
    return 0;
}
