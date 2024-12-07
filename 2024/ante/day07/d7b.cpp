#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


llint concat(llint a, llint b) {
  if (b == 0)
    return a*10;
  for (llint x = b; x > 0; x /= 10)
    a = a*10;
  return a+b;
}


bool possible(vector<llint> &s, llint target) {
  queue<pair<int, llint>> q;
  q.push({1, s[0]});
  while (!q.empty()) {
    auto p = q.front(); q.pop();

    int i = p.first;
    llint y = p.second;
  
    if (y == target && i == (int)s.size())
      return true;

    if (i >= (int)s.size())
      continue; 

    q.push({i+1, y + s[i]});
    q.push({i+1, y * s[i]});
    q.push({i+1, concat(y, s[i])});
  }
  return false;
}


int main() {
  llint total = 0;
  
  string line;
  while (getline(cin, line)) {
    istringstream in(line);
    long long target;
    char c;
    in >> target >> c;
    assert(c == ':');
    vector<llint> s;
    int x;
    while (in >> x)
      s.push_back(x);
    if (possible(s, target))
      total += target;
  }

  cout << total << endl;
  return 0;
}
