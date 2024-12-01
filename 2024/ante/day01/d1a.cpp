#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


int main() {
  vector<int> a;
  vector<int> b;

  int x, y;
  while (cin >> x >> y) {
    a.push_back(x);
    b.push_back(y);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  int total = 0;
  for (int i=0; i<(int)a.size(); i++)
    total += abs(a[i]-b[i]);

  cout << total << endl;
  
  return 0;
}
