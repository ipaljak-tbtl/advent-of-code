#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


int main() {
  int p[2] = {0, 0};
  scanf("Player 1 starting position: %d\n", &p[0]);
  scanf("Player 2 starting position: %d\n", &p[1]);
  p[0]--;
  p[1]--;
  int k = 0;
  int s[2] = {0, 0};
  while (s[0] < 1000 && s[1] < 1000) {
    p[k%2] += 3*(3*k+2);
    p[k%2] %= 10;
    s[k%2] += p[k%2]+1;
    k++;
  }
  cout << min(s[0], s[1])*k*3 << endl;
  return 0;
}
