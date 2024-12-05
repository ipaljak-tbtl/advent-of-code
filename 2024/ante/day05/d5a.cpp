#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

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
    if (good(s))
      total += s[(int)s.size()/2];
  } while (cin >> line);

  cout << total << endl;
  return 0;
}
