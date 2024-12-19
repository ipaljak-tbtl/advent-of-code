#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

vector<string> split(string s) {
  vector<string> ret;
  stringstream ss(s);
  string w;
  while (ss >> w) {
    if (w.ends_with(","))
      w.pop_back();
    ret.push_back(w);
  }
  return ret;
}


vector<string> items;

int possible(string s) {
  int n = s.size();
  vector<int> dp(n+1, 0);
  dp[0] = 1;
  for (int i=0; i<n; i++)
    if (dp[i])
      for (auto x : items)
        if (s.substr(i, x.size()) == x)
          dp[i+x.size()] = 1;
  return dp[n];
}

int main() {
  string line;
  getline(cin, line);
  items = split(line);

  int count = 0;
  while (cin >> line)
    if (possible(line))
      count++;

  cout << count << endl;
  return 0;
}
