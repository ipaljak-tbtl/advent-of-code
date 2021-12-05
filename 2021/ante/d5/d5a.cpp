#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  map<pair<int, int>, int> freq;

  int x1, y1, x2, y2;
  while (scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
    if (x1 != x2 && y1 != y2)
      continue ;
    for (int x=min(x1, x2); x<=max(x1, x2); x1!=x2?x++)
      for (int y=min(y1, y2); y<=max(y1, y2); y1!=y2?y++)
        freq[{x, y}]++;
  }
  
  int count = 0;
  for (auto &a : freq)
    if (a.second > 1)
      count++;

  printf("%d\n", count);
  return 0;
}
