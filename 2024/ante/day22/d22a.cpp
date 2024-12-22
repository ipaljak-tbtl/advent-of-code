#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

const int MOD = 16777216;

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

int main() {
  llint x;
  llint total = 0;
  
  while (cin >> x)
    total += forward(x, 2000);
  cout << total << endl;
  
  return 0;
}
