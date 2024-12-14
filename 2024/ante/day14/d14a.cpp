#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

const int NX = 101;
const int NY = 103;

vector<int> x;
vector<int> y;
vector<int> dx;
vector<int> dy;

int main() {
  int ax, ay, adx, ady;
  while (scanf(" p=%d,%d v=%d,%d", &ax, &ay, &adx, &ady) == 4) {
    x.push_back(ax);
    y.push_back(ay);
    dx.push_back(adx);
    dy.push_back(ady);
  }

  llint q1 = 0;
  llint q2 = 0;
  llint q3 = 0;
  llint q4 = 0;

  for (int i=0; i<(int)x.size(); i++) {
    int X = ((x[i]+100*dx[i])%NX+NX)%NX;
    int Y = ((y[i]+100*dy[i])%NY+NY)%NY;
    if (X < NX/2 && Y < NY/2) q1++;
    if (X < NX/2 && Y > NY/2) q2++;
    if (X > NX/2 && Y < NY/2) q3++;
    if (X > NX/2 && Y > NY/2) q4++;
  } 

  cout << q1*q2*q3*q4 << endl;
  return 0;
}
