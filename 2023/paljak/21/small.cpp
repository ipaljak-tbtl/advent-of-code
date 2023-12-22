#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250;

const int dr[] = {1, 0, -1, 0};
const int ds[] = {0, 1, 0, -1};

int n;

char grid[MAXN][MAXN];

inline bool check(int r, int s) {
  return r >= 0 && r < n && s >= 0 && s < n && grid[r][s] != '#';
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1);
  --n;

  set<pair<int, int>> curr, nxt;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (grid[i][j] == 'S') curr.insert({i, j});

  for (int i = 0; i < 64; ++i) {
    for (auto &p : curr) {
      for (int k = 0; k < 4; ++k) {
        int r = p.first + dr[k], s = p.second + ds[k];
        if (!check(r, s)) continue;
        nxt.insert({r, s});
      }
    }
    curr = nxt;
    nxt.clear();
  }

  printf("%d\n", (int) curr.size());

  return 0;
}
