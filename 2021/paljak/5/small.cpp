#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000;

int a, b, c, d, sol;
int cnt[MAX][MAX];

int vec(int a, int b) {
  if (a == b) return 0;
  return (a - b) / abs(a - b);
}

int main(void) {
  while (scanf("%d,%d -> %d,%d", &a, &b, &c, &d) != EOF) {
    if (a != c && b != d) continue;
    int dx = vec(a, c), dy = vec(b, d);
    while (a + dx != c || b + dy != d) {
      sol += (++cnt[c][d]) == 2;
      c += dx, d += dy;
    };
  }

  printf("%d\n", sol);

  return 0;
}
