/*
--- Part Two ---
The sandstorm is upon you and you aren't any closer to escaping the wasteland.
You had the camel follow the instructions, but you've barely left your starting
position. It's going to take significantly more steps to escape!

What if the map isn't for people - what if the map is for ghosts? Are ghosts
even bound by the laws of spacetime? Only one way to find out.

After examining the maps a bit longer, your attention is drawn to a curious
fact: the number of nodes with names ending in A is equal to the number ending
in Z! If you were a ghost, you'd probably just start at every node that ends
with A and follow all of the paths at the same time until they all
simultaneously end up at nodes that end with Z.

For example:

LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)
Here, there are two starting nodes, 11A and 22A (because they both end with A).
As you follow each left/right instruction, use that instruction to
simultaneously navigate away from both nodes you're currently on. Repeat this
process until all of the nodes you're currently on end with Z. (If only some of
the nodes you're on end with Z, they act like any other node and you continue as
normal.) In this example, you would proceed as follows:

Step 0: You are at 11A and 22A.
Step 1: You choose all of the left paths, leading you to 11B and 22B.
Step 2: You choose all of the right paths, leading you to 11Z and 22C.
Step 3: You choose all of the left paths, leading you to 11B and 22Z.
Step 4: You choose all of the right paths, leading you to 11Z and 22B.
Step 5: You choose all of the left paths, leading you to 11B and 22C.
Step 6: You choose all of the right paths, leading you to 11Z and 22Z.
So, in this example, you end up entirely on nodes that end in Z after 6 steps.

Simultaneously start on every node that ends with A. How many steps does it take
before you're only on nodes that end with Z?
*/

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

long getLcm(vector<int> arr) {
  long res = 1;
  for (int i = 0; i < arr.size(); i++) {
    res = lcm(res, arr[i]);
  }
  return res;
}

vector<int> followMap(string instructions, vector<string> nodes,
                      unordered_map<string, pair<string, string>> m) {
  int i = 0;
  vector<int> steps(nodes.size(), 0);

  int doneCount = 0;
  while (doneCount != nodes.size()) {
    if (i >= instructions.length()) i = 0;

    char instruction = instructions[i];
    for (int j = 0; j < nodes.size(); j++) {
      string n = nodes[j];
      if (n[2] == 'Z') continue;

      pair<string, string> lr = m[n];
      if (instruction == 'L') {
        n = lr.first;
      } else {
        n = lr.second;
      }

      nodes[j] = n;
      steps[j]++;
      if (n[2] == 'Z') doneCount++;
    }

    i++;
  }

  return steps;
}

int main() {
  fstream file;
  file.open("input.txt", ios::in);

  if (!file.is_open()) {
    cout << "Couldn't open file";
    return 0;
  }

  string instructions;
  getline(file, instructions);

  string nextLine;
  getline(file, nextLine);  // remove blank 2nd line
  unordered_map<string, pair<string, string>> m;
  vector<string> nodes;
  while (getline(file, nextLine)) {
    string n = nextLine.substr(0, 3);
    string l = nextLine.substr(7, 3);
    string r = nextLine.substr(12, 3);
    pair<string, string> p(l, r);
    m[n] = p;

    if (n[2] == 'A') {
      nodes.push_back(n);
    }
  }

  vector<int> stepsPerNode = followMap(instructions, nodes, m);
  cout << getLcm(stepsPerNode) << endl;

  file.close();
  return 0;
}
