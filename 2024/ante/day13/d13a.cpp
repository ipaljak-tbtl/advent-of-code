#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;


int best(int ax, int ay, int bx, int by, int X, int Y) {
  int res = 0;
  for (int A=0; A<=100; A++)
    for (int B=0; B<=100; B++) {
      int rx = A*ax + B*bx;
      int ry = A*ay + B*by;
      int cost = 3*A + B;
      if (rx == X && ry == Y)
        if (res == 0 || cost < res)
          res = cost;
    }
  return res;
}


int main() {
  int ax, ay;
  int bx, by;
  int X, Y;

  int total = 0;
  while(scanf(" Button A: X+%d, Y+%d", &ax, &ay) == 2) {
    scanf(" Button B: X+%d, Y+%d", &bx, &by);
    scanf(" Prize: X=%d, Y=%d", &X, &Y);
    total += best(ax, ay, bx, by, X, Y);
  }
  cout << total << endl;
  return 0;
}
