#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


vector<vector<int>> keys;
vector<vector<int>> locks;


vector<int> count(const vector<string> &s) {
  vector<int> r(s[0].size(), 0);
  for (int i=0; i<(int)s.size(); i++)
    for (int j=0; j<(int)s[i].size(); j++)
      if (s[i][j] == '#')
        r[j]++;
  return r;
}


int fits(const vector<int> key, const vector<int> lock) {
  for (int i=0; i<5; i++)
    if (key[i] + lock[i] > 7)
      return 0;
  return 1;
}


int main() {
  string line;
  while (cin >> line) {
    vector<string> current;
    current.push_back(line);
    for (int i=0; i<6; i++) {
      cin >> line;
      current.push_back(line);
    }

    auto nums = count(current);
    if (current[0][0] == '#')
      locks.push_back(nums);
    else
      keys.push_back(nums);
  }

  int total = 0;
  for (auto k : keys)
    for (auto l : locks)
      if (fits(k, l))
        total++;

  cout << total << endl;
  
  return 0;
}
