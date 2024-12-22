#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

const int MOD = 16777216;

map<vector<int>, int> total;


llint next(llint s) {
  s = (s ^ (s * 64)) % MOD;
  s = (s ^ (s / 32)) % MOD;
  s = (s ^ (s * 2048)) % MOD;
  return s;
}


llint forward(llint s, llint c) {
  for (int i=0; i<c; i++)
    s = next(s);
  return s;
}


void process(llint s) {
  vector<int> deltas;
  set<vector<int>> done;
  
  for (int i=0; i<2000; i++) {
    
    llint l = s;
    s = next(s);

    int d = (s%10)-(l%10);
    deltas.push_back(d);

    if ((int)deltas.size() > 4)
      deltas.erase(deltas.begin());

    if ((int)deltas.size() == 4 && !done.count(deltas)) {
      total[deltas] += s%10;
      done.insert(deltas);
    }
  }
}


int main() {
  llint x;
  
  while (cin >> x) {
    process(x);
  }

  int sol = -1;
  for (auto &[a, b] : total) {
    sol = max(sol, b);
  }

  cout << sol << endl;
  
  return 0;
}
