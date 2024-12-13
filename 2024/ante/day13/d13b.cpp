#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

llint best(llint ax, llint ay, llint bx, llint by, llint X, llint Y) {
  llint det = ax*by - ay*bx;
  if (det == 0) {
    if (ax*Y != ay*X)
      return 0;
    if (bx*Y != by*X)
      return 0;  
    // Infinitely many solutions - find minimum cost one
    // Turns not no need for this
    assert(false);
  }
  llint A = (X*by - Y*bx) / det;
  llint B = (Y*ax - X*ay) / det;  
  if (A < 0 || B < 0)
    return 0;
  if (A*ax + B*bx != X)
    return 0;
  if (A*ay + B*by != Y)
    return 0;
  
  return 3*A + B;
}

int main() {
  llint ax, ay;
  llint bx, by;
  llint X, Y;

  llint total = 0;
  while(scanf(" Button A: X+%lld, Y+%lld", &ax, &ay) == 2) {
    scanf(" Button B: X+%lld, Y+%lld", &bx, &by);
    scanf(" Prize: X=%lld, Y=%lld", &X, &Y);
    X += 10000000000000;
    Y += 10000000000000;
    total += best(ax, ay, bx, by, X, Y);
  }
  cout << total << endl;
  return 0;
}
