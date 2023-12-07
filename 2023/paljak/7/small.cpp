#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

struct hand {
  string cards;
  int bid;

  hand() {}
  hand(string cards, int bid): cards(cards), bid(bid) {}

  int type() const {
    map<char, int> cnt;
    for (auto c : cards)
      cnt[c]++;

    int two = 0, three = 0;
    for (const auto &p : cnt) {
      if (p.second == 5) return 7;
      if (p.second == 4) return 6;
      three += p.second == 3;
      two += p.second == 2;
    }

    if (three == 1 && two == 1) return 5;
    if (three == 1) return 4;
    if (two == 2) return 3;
    if (two == 1) return 2;
    return 1;
  }

  friend bool operator < (const hand &A, const hand &B) {
    int a_type = A.type(), b_type = B.type();
    if (a_type != b_type) return a_type < b_type;

    const string strength = "AKQJT98765432";
    for (int i = 0; i < 5; ++i) {
      int a_strength = strength.find(A.cards[i]);
      int b_strength = strength.find(B.cards[i]);
      if (a_strength != b_strength) return a_strength > b_strength;
    }

    assert(false);
  }
};

vector<hand> hands;

int main(void) {
  string cards;
  int bid;
  while (cin >> cards >> bid)
    hands.emplace_back(cards, bid);

  sort(hands.begin(), hands.end());

  llint sol = 0;
  for (int i = 0; i < (int)hands.size(); ++i)
    sol += (llint) hands[i].bid * (i + 1);

  cout << sol << "\n";

  return 0;
}
