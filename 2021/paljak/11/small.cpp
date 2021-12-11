#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

const int dr[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int ds[] = {-1, 0, 1, 1, 1, 0, -1, -1};

int r = 10, s = 10;
char grid[MAXN][MAXN];

inline bool inside(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s;
}

int step() {
  queue<pair<int, int>> Q;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (grid[i][j] == '9') {
        Q.push({i, j});
        grid[i][j] = -1;
      } else {
        grid[i][j]++;
      }
    }
  }

  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();
    for (int i = 0; i < 8; ++i) {
      int rr = curr.first + dr[i], ss = curr.second + ds[i];
      if (!inside(rr, ss) || grid[rr][ss] == -1) continue;
      ++grid[rr][ss];
      if (grid[rr][ss] - '0' == 10) {
        grid[rr][ss] = -1;
        Q.push({rr, ss});
      }
    }
  }

  int ret = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] == -1) ++ret, grid[i][j] = '0';

  return ret;
}

int main(void) {
  for (int i = 0; i < r; ++i)
    scanf("%s", grid[i]);

  int sol = 0;
  for (int t = 0; t < 100; ++t)
    sol += step();

  printf("%d\n", sol);
  return 0;
}
