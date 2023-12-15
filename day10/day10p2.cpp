/*
--- Part Two ---
You quickly reach the farthest point of the loop, but the animal never emerges.
Maybe its nest is within the area enclosed by the loop?

To determine whether it's even worth taking the time to search for such a nest,
you should calculate how many tiles are contained within the loop. For example:

...........
.S-------7.
.|F-----7|.
.||.....||.
.||.....||.
.|L-7.F-J|.
.|..|.|..|.
.L--J.L--J.
...........
The above loop encloses merely four tiles - the two pairs of . in the southwest
and southeast (marked I below). The middle . tiles (marked O below) are not in
the loop. Here is the same loop again with those regions marked:

...........
.S-------7.
.|F-----7|.
.||OOOOO||.
.||OOOOO||.
.|L-7OF-J|.
.|II|O|II|.
.L--JOL--J.
.....O.....
In fact, there doesn't even need to be a full tile path to the outside for tiles
to count as outside the loop - squeezing between pipes is also allowed! Here, I
is still within the loop and O is still outside the loop:

..........
.S------7.
.|F----7|.
.||OOOO||.
.||OOOO||.
.|L-7F-J|.
.|II||II|.
.L--JL--J.
..........
In both of the above examples, 4 tiles are enclosed by the loop.

Here's a larger example:

.F----7F7F7F7F-7....
.|F--7||||||||FJ....
.||.FJ||||||||L7....
FJL7L7LJLJ||LJ.L-7..
L--J.L7...LJS7F-7L7.
....F-J..F7FJ|L7L7L7
....L7.F7||L7|.L7L7|
.....|FJLJ|FJ|F7|.LJ
....FJL-7.||.||||...
....L---J.LJ.LJLJ...
The above sketch has many random bits of ground, some of which are in the loop
(I) and some of which are outside it (O):

OF----7F7F7F7F-7OOOO
O|F--7||||||||FJOOOO
O||OFJ||||||||L7OOOO
FJL7L7LJLJ||LJIL-7OO
L--JOL7IIILJS7F-7L7O
OOOOF-JIIF7FJ|L7L7L7
OOOOL7IF7||L7|IL7L7|
OOOOO|FJLJ|FJ|F7|OLJ
OOOOFJL-7O||O||||OOO
OOOOL---JOLJOLJLJOOO
In this larger example, 8 tiles are enclosed by the loop.

Any tile that isn't part of the main loop can count as being enclosed by the
loop. Here's another example with many bits of junk pipe lying around that
aren't connected to the main loop at all:

FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJ7F7FJ-
L---JF-JLJ.||-FJLJJ7
|F|F-JF---7F7-L7L|7|
|FFJF7L7F-JF7|JL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L
Here are just the tiles that are enclosed by the loop marked with I:

FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJIF7FJ-
L---JF-JLJIIIIFJLJJ7
|F|F-JF---7IIIL7L|7|
|FFJF7L7F-JF7IIL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L
In this last example, 10 tiles are enclosed by the loop.

Figure out whether you have time to search for the nest by calculating the area
within the loop. How many tiles are enclosed by the loop?
*/

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<vector<bool>> getLoop(pair<int, int> start, vector<string> g) {
  const int ROWS = g.size();
  const int COLS = g[0].length();
  set<pair<int, int>> visited;
  queue<pair<int, int>> q;
  q.push(start);

  vector<vector<bool>> isLoop;
  for (int r = 0; r < ROWS; r++) {
    vector<bool> row(COLS, false);
    isLoop.push_back(row);
  }

  while (q.size()) {
    pair<int, int> cord = q.front();
    q.pop();

    int r = cord.first;
    int c = cord.second;
    visited.insert(cord);
    isLoop[r][c] = true;

    pair<int, int> pUp(r - 1, c);
    if (r - 1 >= 0 && !visited.count(pUp) &&
        (g[r - 1][c] == '|' || g[r - 1][c] == '7' || g[r - 1][c] == 'F')) {
      q.push(pUp);
    }

    pair<int, int> pDown(r + 1, c);
    if (r + 1 < ROWS && !visited.count(pDown) &&
        (g[r + 1][c] == '|' || g[r + 1][c] == 'L' || g[r + 1][c] == 'J')) {
      q.push(pDown);
    }

    pair<int, int> pRight(r, c + 1);
    if (c + 1 < COLS && !visited.count(pRight) &&
        (g[r][c + 1] == '-' || g[r][c + 1] == '7' || g[r][c + 1] == 'J')) {
      q.push(pRight);
    }

    pair<int, int> pLeft(r, c - 1);
    if (c - 1 >= 0 && !visited.count(pLeft) &&
        (g[r][c - 1] == '-' || g[r][c - 1] == 'L' || g[r][c - 1] == 'F')) {
      q.push(pLeft);
    }
  }

  return isLoop;
}

int main() {
  std::fstream file;
  file.open("input.txt", std::ios::in);

  if (!file.is_open()) {
    std::cout << "Couldn't open file";
    return 0;
  }

  std::string nextLine;
  vector<string> g;
  while (getline(file, nextLine)) {
    g.push_back(nextLine);
  }

  int ROWS = g.size();
  int COLS = g[0].length();
  vector<vector<int>> distances;
  for (int r = 0; r < ROWS; r++) {
    vector<int> row(COLS, 0);
    distances.push_back(row);
  }

  vector<vector<bool>> isLoop;
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      if (g[r][c] == 'S') {
        pair<int, int> start(r, c);
        isLoop = getLoop(start, g);
      }
    }
  }

  int insideCount = 0;
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      if (isLoop[r][c]) continue;

      int crosses = 0;
      int nr = r;
      int nc = c;
      while (nr < ROWS && nc < COLS) {
        if (!isLoop[nr][nc] && g[nr][nc] != 'L' && g[nr][nc] != '7') crosses++;
        nr++;
        nc++;
      }

      if (crosses % 2 == 1) insideCount++;
    }
  }

  cout << insideCount << endl;

  file.close();
  return 0;
}
