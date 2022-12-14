#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

const int dr[] = {1, 1, 1};
const int ds[] = {0, -1, 1};

char grid[MAXN][MAXN];

int maxr = 0;

void parse_grid() {
  int pr, ps;
  while (scanf("%d,%d", &ps, &pr) != EOF) {
    maxr = max(maxr, pr);
    int r, s;
    while (scanf(" -> %d,%d", &s, &r) == 2) {
      maxr = max(maxr, r);
      do {
        grid[pr][ps] = '#';
        if (r != pr) pr += (r - pr) / abs(r - pr);
        if (s != ps) ps += (s - ps) / abs(s - ps);
      } while (r != pr || s != ps);
      grid[pr][ps] = '#';
    }
  }

  for (int i = 0; i < 1000; ++i)
    grid[maxr + 2][i] = '#';
}

bool fall() {
  int r = 0, s = 500;
  while (r <= 1000) {
    bool ok = false;
    for (int i = 0; i < 3; ++i) {
      int rr = r + dr[i], ss = s + ds[i];
      if (grid[rr][ss] == '.') {
        ok = true;
        r = rr; s = ss;
        break;
      }
    }
    if (!ok) break;
  }
  grid[r][s] = 'o';
  return r != 0;
}

int main(void) {
  memset(grid, '.', sizeof grid);
  parse_grid();

  int sol = 0;
  while (fall()) ++sol;

  printf("%d\n", sol + 1);
  return 0;
}
