#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> diff;

int main(void) {
  string cmd;
  int cycle = 0;
  diff.emplace_back(1, 1);
  while (cin >> cmd) {
    if (cmd == "noop") {
      ++cycle;
    } else {
      cycle += 2;
      int dx;
      cin >> dx;
      diff.emplace_back(cycle, dx);
    }
  }

  int sol = 0, q = 20, curr = 0;
  for (auto &p : diff) {
    if (q > 220) break;
    while (p.first >= q) {
      sol += q * curr;
      q += 40;
    }
    curr += p.second;
  }

  cout << sol << endl;
  return 0;
}
