#include <algorithm>
#include <cstdio>

using namespace std;

int x1, y1, x2, y2;

inline bool check(int vx, int vy) {
  int x = 0, y = 0;
  while (y >= y1 && !((x < x1 || x > x2) && vx == 0)) {
    x += vx, y += vy;
    vx -= (vx > 0), --vy;
    if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
      return true;
  }
  return false;
}

int main(void) {
  scanf("target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);

  int sol = 0;
  for (int vx = 0; vx <= x2; ++vx)
    for (int vy = y1; vy <= -y1; ++vy)
      sol += check(vx, vy);

  printf("%d\n", sol);
  return 0;
}
