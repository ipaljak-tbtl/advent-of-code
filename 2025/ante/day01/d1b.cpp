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
    if (c == 'L') {
      if (curr == 0)
        cnt--;
      curr = curr - d;
      if (curr <= 0)
        cnt += -curr/100+1;
      curr = (curr%100 + 100) % 100;
    }
    else
      curr = curr + d;
      cnt += curr/100;
      curr = curr % 100;
  }
  cout << cnt << endl;
  return 0;
}
