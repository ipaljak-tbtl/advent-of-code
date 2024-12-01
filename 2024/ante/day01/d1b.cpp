#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

int main() {
  vector<int> a;
  map<int, int> b;

  int x, y;
  while (cin >> x >> y) {
    a.push_back(x);
    b[y]++;
  }

  llint total = 0;
  for (int i=0; i<(int)a.size(); i++)
    total += a[i]*b[a[i]];

  cout << total << endl;
  
  return 0;
}
