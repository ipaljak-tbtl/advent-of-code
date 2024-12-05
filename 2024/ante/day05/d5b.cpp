#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

set<pair<int, int>> before;


vector<int> parse(const string s) {
  istringstream in(s);
  vector<int> out;
  int x;
  while (in >> x) {
    out.push_back(x);
    char c;
    if (in >> c)
      assert(c == ',');
    else
      break ;
  }
  return out;
}


int good(const vector<int> &s) {
  for (int i=0; i<(int)s.size(); i++)
    for (int j=i+1; j<(int)s.size(); j++)
      if (before.count({s[j], s[i]}))
          return 0;
  return 1;
}


int middle(const vector<int> &s) {
  int n = s.size();
  vector<int> h(n, 0);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      if (before.count({s[j], s[i]}))
        h[i]++;
  
  // sort(h.begin(), h.end());
  // for (int i=0; i<n; i++)
  //   assert(h[i] == i);

  for (int i=0; i<n; i++)
    if (h[i] == n/2)
      return s[i];

  assert(false);
  return -1;
}


int main() {
  string line;
  while (cin >> line) {
    int a, b;
    if (sscanf(line.c_str(), "%d|%d", &a, &b) != 2)
      break ;
    before.insert({a, b});
    
  }

  int total = 0;
  do {
    vector<int> s = parse(line);
    if (!good(s))
      total += middle(s);
  } while (cin >> line);

  cout << total << endl;
  return 0;
}
