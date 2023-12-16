#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

// RDLU
const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

int n;

bool been[MAXN][MAXN][MAXN];
char grid[MAXN][MAXN];

inline bool check(const int r, const int s) {
  return min(r, s) >= 0 && max(r, s) < n;
}

void dfs(int r, int s, int dir) {
  if (!check(r, s)) return;
  if (been[r][s][dir]) return;
  been[r][s][dir] = true;

  if (grid[r][s] == '.' ||
     (grid[r][s] == '|' && dir % 2 == 1) ||
     (grid[r][s] == '-' && dir % 2 == 0)) {
    dfs(r + dr[dir], s + ds[dir], dir);
    return;
  }

  if (grid[r][s] == '\\') {
    int _dir = dir ^ 1;
    dfs(r + dr[_dir], s + ds[_dir], _dir);
  }

  if (grid[r][s] == '/') {
    int _dir = ((((dir + 1) % 4) ^ 1) + 3) % 4;
    dfs(r + dr[_dir], s + ds[_dir], _dir);
  }

  if (grid[r][s] == '|' || grid[r][s] == '-')
    for (int i = 0; i < 4; ++i)
      if (i % 2 != dir % 2)
        dfs(r + dr[i], s + ds[i], i);
}

int solve(int r, int s, int dir) {
  memset(been, false, sizeof been);
  dfs(r, s, dir);
  int ret = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      ret += been[i][j][0] | been[i][j][1] | been[i][j][2] | been[i][j][3];
  return ret;
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1);
  --n;

  dfs(0, 0, 0);

  int sol = 0;
  for (int i = 0; i < n; ++i) {
    sol = max(sol, solve(i, 0, 0));
    sol = max(sol, solve(i, n - 1, 2));
    sol = max(sol, solve(0, i, 1));
    sol = max(sol, solve(i, n - 1, 3));
  }

  printf("%d\n", sol);

  return 0;
}
