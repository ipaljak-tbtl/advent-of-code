#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

int r, s;
char grid[MAXN][MAXN];

inline bool inside(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s;
}

int scenic(int rr, int ss) {
  int ret = 1;
  for (int k = 0; k < 4; ++k) {
    int _r = rr + dr[k], _s = ss + ds[k], cnt = 0;
    while (inside(_r, _s)) {
      ++cnt;
      if (grid[_r][_s] >= grid[rr][ss])
        break;
      _r += dr[k]; _s += ds[k];
    }
    ret *= cnt;
  }
  return ret;
}

int main(void) {
  while (scanf("%s", grid[r]) != EOF) {
    s = strlen(grid[r]);
    ++r;
  }

  int sol = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      sol = max(sol, scenic(i, j));

  printf("%d\n", sol);
  return 0;
}
