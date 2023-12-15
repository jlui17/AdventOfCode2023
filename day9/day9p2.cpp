/*
--- Part Two ---
Of course, it would be nice to have even more history included in your report.
Surely it's safe to just extrapolate backwards as well, right?

For each history, repeat the process of finding differences until the sequence
of differences is entirely zero. Then, rather than adding a zero to the end and
filling in the next values of each previous sequence, you should instead add a
zero to the beginning of your sequence of zeroes, then fill in new first values
for each previous sequence.

In particular, here is what the third example history looks like when
extrapolating back in time:

5  10  13  16  21  30  45
  5   3   3   5   9  15
   -2   0   2   4   6
      2   2   2   2
        0   0   0
Adding the new values on the left side of each sequence from bottom to top
eventually reveals the new left-most history value: 5.

Doing this for the remaining example data above results in previous values of -3
for the first history and 0 for the second history. Adding all three new values
together produces 2.

Analyze your OASIS report again, this time extrapolating the previous value for
each history. What is the sum of these extrapolated values?
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

long getNext(vector<long> history) {
  vector<vector<long>> diffs{history};
  while (true) {
    bool allZeros = true;
    vector<long> lastDiffs = diffs[diffs.size() - 1];
    vector<long> nextDiffs;

    for (int i = 1; i < lastDiffs.size(); i++) {
      long d = lastDiffs[i] - lastDiffs[i - 1];
      if (allZeros && d != 0) allZeros = false;
      nextDiffs.push_back(d);
    }

    if (allZeros) break;
    diffs.push_back(nextDiffs);
  }

  long res = 0;
  for (int i = diffs.size() - 1; i >= 0; i--) {
    res = diffs[i][0] - res;
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
  vector<vector<long>> histories;
  while (getline(file, nextLine)) {
    vector<string> hs = split(nextLine, ' ');
    vector<long> history;
    for (string s : hs) {
      history.push_back(stol(s));
    }
    histories.push_back(history);
  }

  long res = 0;
  for (auto h : histories) {
    res += getNext(h);
  }
  cout << res << endl;
}
