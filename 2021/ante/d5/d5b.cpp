#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  map<pair<int, int>, int> freq;

  int x1, y1, x2, y2;
  while (scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
    int x=x1;
    int y=y1;
    while (x != x2 || y != y2) {
      freq[{x, y}]++;
      if (x1 < x2)
        x++;
      if (x1 > x2)
        x--;
      if (y1 < y2)
        y++;
      if (y1 > y2)
        y--;
    }
    freq[{x2, y2}]++;
  }
  
  int count = 0;
  for (auto &a : freq)
    if (a.second > 1)
      count++;

  printf("%d\n", count);
  return 0;
}
