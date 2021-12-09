#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;

const int dr[] = {0, 1, -1, 0};
const int ds[] = {1, 0, 0, -1};

int r, s;
char grid[MAXN][MAXN];

bool bio[MAXN][MAXN];

bool inside(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s;
}

int dfs(int i, int j) {
  if (bio[i][j] || grid[i][j] == '9') return 0;
  bio[i][j] = true;
  int ret = 1;
  for (int k = 0; k < 4; ++k) {
    int ii = i + dr[k], jj = j + ds[k];
    if (!inside(ii, jj)) continue;
    if (grid[ii][jj] >= grid[i][j])
      ret += dfs(ii, jj);
  }
  return ret;
}

int main(void) {
  while (scanf("%s", grid[r]) == 1) ++r;
  s = strlen(grid[0]);

  vector<int> v;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      bool low = true;
      for (int k = 0; k < 4; ++k) {
        int ii = i + dr[k], jj = j + ds[k];
        if (!inside(ii, jj)) continue;
        low &= grid[ii][jj] > grid[i][j];
      }
      if (low) v.emplace_back(dfs(i, j));
    }
  }

  int vs = v.size();
  sort(v.begin(), v.end());

  int sol = v[vs - 1] * v[vs - 2] * v[vs - 3];
  printf("%d\n", sol);

  return 0;
}
