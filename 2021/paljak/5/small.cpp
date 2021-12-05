#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000;

int cnt[MAX][MAX];

int vec(int a, int b) {
  if (a == b) return 0;
  return (a - b) / abs(a - b);
}

int main(void) {
  int a, b, c, d;
  while (scanf("%d,%d -> %d,%d", &a, &b, &c, &d) != EOF) {
    if (a != c && b != d) continue;
    int dx = vec(a, c), dy = vec(b, d);
    while (a + dx != c || b + dy != d) {
      ++cnt[c][d];
      c += dx, d += dy;
    };
  }

  int sol = 0;
  for (int i = 0; i < MAX; ++i)
    for (int j = 0; j < MAX; ++j)
      sol += cnt[i][j] > 1;

  printf("%d\n", sol);

  return 0;
}
