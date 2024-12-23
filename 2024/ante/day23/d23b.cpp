#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


map<string, set<string>> L;
vector<string> nodes;


string best_clique(string x) {
  int b = 0;
  int n = L[x].size();
  
  vector<string> y(L[x].begin(), L[x].end());
  int g[n][n];
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      g[i][j] = L[y[i]].count(y[j]);
  
  for (int mask=1; mask<(1<<n); mask++) {
    int good = 1;
    for (int i=0; i<n; i++)
      if ((mask>>i)&1)
        for (int j=i+1; j<n; j++)
          if ((mask>>j)&1)
            if (!g[i][j])
              good = 0;
    
    if (good && __builtin_popcount(mask) > __builtin_popcount(b))
      b = mask;
  }

  vector<string> c;
  c.push_back(x);
  for (int i=0; i<n; i++)
    if ((b>>i)&1)
      c.push_back(y[i]);
  sort(c.begin(), c.end());

  string res;
  int first = 1;
  for (auto x : c) {
    if (!first)
      res += ",";
    res += x;
    first = 0;
  }

  return res;
}


int main() {
  string line;
  while (cin >> line) {
    string a = string() + line[0] + line[1];
    string b = string() + line[3] + line[4];
    L[a].insert(b);
    L[b].insert(a);
  }

  int max_degree = 0;
  for (auto &[a, la] : L) {
    nodes.push_back(a);
    max_degree = max(max_degree, (int)la.size());
  }
  TRACE(nodes.size());
  TRACE(max_degree);

  string best;
  for (auto x : nodes) {
    string c = best_clique(x);
    if (c.size() > best.size())
      best = c;
  }

  cout << best << endl;
  return 0;
}
