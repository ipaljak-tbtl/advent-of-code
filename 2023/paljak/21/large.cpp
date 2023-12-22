#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 250;

const int dr[] = {1, 0, -1, 0};
const int ds[] = {0, 1, 0, -1};

int n;
int ff[350];

char grid[MAXN][MAXN];

void f(int x) {
  set<pair<int, int>> curr, nxt;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (grid[i][j] == 'S') curr.insert({i, j});

  for (int i = 0; i < x; ++i) {
    for (auto &p : curr) {
      for (int k = 0; k < 4; ++k) {
        int r = p.first + dr[k], s = p.second + ds[k];
        if (grid[(r + 5000 * n) % n][(s + 5000 * n) % n] == '#') continue;
        nxt.insert({r, s});
      }
    }
    ff[i] = (int) curr.size();
    curr = nxt;
    nxt.clear();
  }

  ff[x] = (int) curr.size();
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1);
  --n;

  f(65 + 2 * n);

  int y1 = ff[65], y2 = ff[65 + n], y3 = ff[65 + 2 * n];
  int s = 26501365 / n;

  printf("%lld\n", (llint) y1 + (llint) (y2 - y1) * s + (llint) (y3 - 2LL*y2 + y1) * s * (s - 1) / 2LL);

  return 0;
}
