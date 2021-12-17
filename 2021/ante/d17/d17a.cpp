#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int hits(int x, int y, int x0, int x1, int y0, int y1) {
  int cx = 0;
  int cy = 0;
  int hiy = 0;
  while (cx <= x1 && cy >= y0) {
    if (cx >= x0 && cy <= y1)
      return hiy;
    hiy = max(hiy, cy);
    cx += x;
    cy += y;
    if (x > 0)
      x--;
    y--;
  }
  return -1;
}


int main() {
  int x0, y0, x1, y1;
  scanf(" target area: x=%d..%d, y=%d..%d", &x0, &x1, &y0, &y1);
  if (y0 > y1)
    swap(y0, y1);
  assert(y1 < 0);
  if (x0 > x1)
    swap(x0, x1);
  assert(x0 > 0);

  int hi = 0;
  for (int x=1; x<=x1; x++)
    for (int y=y0; y<=-y0; y++)
      hi = max(hi, hits(x, y, x0, x1, y0, y1));
    
  cout << hi << endl;
  
  return 0;
}
