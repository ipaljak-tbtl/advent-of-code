#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


int main() {
  int t;
  int cnt = 0;
  int curr = 50;

  char c;
  int d;
  while (cin >> ws >> c >> d) {
    if (c == 'L')
      curr = (curr - d + 100) % 100;
    else
      curr = (curr + d) % 100;
    if (curr == 0)
      cnt++;
  }
  cout << cnt << endl;
  return 0;
}
