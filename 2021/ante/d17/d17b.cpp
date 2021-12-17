#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int hits(int x, int y, int x0, int x1, int y0, int y1) {
  int cx = 0;
  int cy = 0;
  while (cx <= x1 && cy >= y0) {
    if (cx >= x0 && cy <= y1)
      return 1;
    cx += x;
    cy += y;
    if (x > 0)
      x--;
    y--;
  }
  return 0;
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

  int count = 0;
  for (int x=1; x<=x1; x++)
    for (int y=y0; y<=-y0; y++)
      if (hits(x, y, x0, x1, y0, y1))
        count++;
    
  cout << count << endl;
  
  return 0;
}
