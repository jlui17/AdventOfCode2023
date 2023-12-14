/*
--- Part Two ---
To make things a little more interesting, the Elf introduces one additional
rule. Now, J cards are jokers - wildcards that can act like whatever card would
make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even
than 2. The other cards stay in the same order: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3,
2, J.

J cards can pretend to be whatever card is best for the purpose of determining
hand type; for example, QJJQ2 is now considered four of a kind. However, for the
purpose of breaking ties between two hands of the same type, J is always treated
as J, not the card it's pretending to be: JKKK2 is weaker than QQQQ2 because J
is weaker than Q.

Now, the above example goes very differently:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
32T3K is still the only one pair; it doesn't contain any jokers, so its strength
doesn't increase. KK677 is now the only two pair, making it the second-weakest
hand. T55J5, KTJJT, and QQQJA are now all four of a kind! T55J5 gets rank 3,
QQQJA gets rank 4, and KTJJT gets rank 5. With the new joker rule, the total
winnings in this example are 5905.

Using the new joker rule, find the rank of every hand in your set. What are the
new total winnings?
*/

#include <fstream>
#include <iostream>
#include <map>
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

enum HAND {
  HIGH,
  ONE,
  TWO,
  THREE,
  FULL,
  FOUR,
  FIVE,
};

HAND getHand(vector<int> c) {
  if (c.size() == 1) return FIVE;
  if (c.size() == 2) {
    if (c[0] == 4 || c[1] == 4) return FOUR;
    return FULL;
  }
  if (c.size() == 3) {
    if (c[0] == 3 || c[1] == 3 || c[2] == 3) return THREE;
    return TWO;
  }
  if (c.size() == 4) return ONE;
  return HIGH;
}

class CardAndBid {
 public:
  string card;
  int bid;
  HAND hand;

  CardAndBid(string line) {
    vector<string> splitLine = split(line, ' ');
    card = splitLine[0];
    bid = stoi(splitLine[1]);

    map<char, int> counts;
    int jCount = 0;
    for (char c : splitLine[0]) {
      if (c == 'J') {
        jCount++;
        continue;
      }

      if (!counts.count(c))
        counts[c] = 1;
      else
        counts[c]++;
    }

    vector<int> v;
    int largest = 0;
    int iLargest = 0;
    int i = 0;
    for (auto it = counts.begin(); it != counts.end(); ++it) {
      int count = it->second;

      if (count > largest) {
        largest = count;
        iLargest = i;
      }
      v.push_back(count);
      i++;
    }

    // case: "JJJJJ", v = []
    if (v.size() == 0) {
      v.push_back(5);
    } else {
      v[iLargest] += jCount;
    }

    hand = getHand(v);
  }

  CardAndBid() {}
};

map<char, int> CARD_SCORES = {
    {'J', 1}, {'2', 2}, {'3', 3},  {'4', 4},  {'5', 5},  {'6', 6}, {'7', 7},
    {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 12}, {'K', 13}, {'A', 14}};

// returns c1 < c2
bool isLessThan(CardAndBid c1, CardAndBid c2) {
  if (c1.hand == c2.hand) {
    for (int i = 0; i < 5; i++) {
      if (c1.card[i] == c2.card[i]) continue;
      return CARD_SCORES[c1.card[i]] < CARD_SCORES[c2.card[i]];
    }
  }

  return c1.hand < c2.hand;
}

/*
  Citation: partition() and quicksort() are modified versions from:
  https://www.geeksforgeeks.org/cpp-program-for-quicksort/
*/
int partition(CardAndBid arr[], int low, int high) {
  // choose the pivot

  CardAndBid pivot = arr[high];
  // Index of smaller element and Indicate
  // the right position of pivot found so far
  int i = (low - 1);

  for (int j = low; j <= high; j++) {
    // If current element is smaller than the pivot
    if (isLessThan(arr[j], pivot)) {
      // Increment index of smaller element
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

// The Quicksort function Implement
void quickSort(CardAndBid arr[], int low, int high) {
  // when low is less than high
  if (low < high) {
    // pi is the partition return index of pivot

    int pi = partition(arr, low, high);

    // Recursion Call
    // smaller element than pivot goes left and
    // higher element goes right
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int main() {
  fstream file;
  file.open("input.txt", ios::in);

  if (!file.is_open()) {
    std::cout << "Couldn't open file";
    return 0;
  }

  vector<CardAndBid> cardsAndBids;
  string nextLine;
  while (getline(file, nextLine)) {
    cardsAndBids.push_back(CardAndBid(nextLine));
  }

  quickSort(cardsAndBids.data(), 0, cardsAndBids.size() - 1);

  long winnings = 0;
  for (int i = 0; i < cardsAndBids.size(); i++) {
    // cout << (i + 1) << ' ' << cardsAndBids[i].card << ' ' <<
    // cardsAndBids[i].bid
    //      << ' ' << cardsAndBids[i].hand << ' ' << cardsAndBids[i].bid * (i +
    //      1)
    //      << endl;
    winnings += cardsAndBids[i].bid * (i + 1);
  }

  cout << winnings << endl;
}
