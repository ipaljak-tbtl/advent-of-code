#include <bits/stdc++.h>

using namespace std;

int main(void) {
  int curr = 0;
  vector<int> cals;

  while (cin.peek() != EOF) {
    string line;
    getline(cin, line);
    if (line.empty()) {
      cals.emplace_back(curr);
      curr = 0;
      continue;
    }
    curr += stoi(line);
  }

  cals.emplace_back(curr);
  sort(cals.rbegin(), cals.rend());

  cout << accumulate(cals.begin(), cals.begin() + 3, 0) << endl;

  return 0;
}
