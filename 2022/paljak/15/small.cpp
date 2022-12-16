#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;
const int Y = 2000000;
const int MAXCOR = 5e6 + 10;

int n;
int sx[MAXN], sy[MAXN], bx[MAXN], by[MAXN];

int main(void) {
  while (scanf("Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &sx[n], &sy[n], &bx[n], &by[n]) != EOF)
    ++n;

  int sol = 0;
  for (int x = -MAXCOR; x <= MAXCOR; ++x) {
    bool add = false;
    for (int i = 0; i < n; ++i) {
      if (bx[i] == x && by[i] == Y) { add = false; break; }
      add |= abs(bx[i] - sx[i]) + abs(by[i] - sy[i]) >= abs(sx[i] - x) + abs(sy[i] - Y);
    }
    sol += add;
  }

  printf("%d\n", sol);
  return 0;
}
