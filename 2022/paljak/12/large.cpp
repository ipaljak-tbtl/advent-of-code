#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

char grid[MAXN][MAXN];

int R, S;
int dist[MAXN][MAXN];

pair<int, int> s, t;

inline bool check(int r, int s) {
  return r >= 0 && r < R && s >= 0 && s < S && dist[r][s] == -1;
}

int main(void) {
  while (scanf("%s", grid[R++]) != EOF);
  S = strlen(grid[0]);

  queue<pair<int, int>> Q;
  memset(dist, -1, sizeof dist);
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < S; ++j) {
      if (grid[i][j] == 'S') grid[i][j] = 'a';
      if (grid[i][j] == 'E') {
        t = {i, j};
        grid[i][j] = 'z';
      }
      if (grid[i][j] == 'a') {
        Q.push({i, j});
        dist[i][j] = 0;
      }
    }
  }

  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();
    for (int i = 0; i < 4; ++i) {
      int r = curr.first + dr[i], s = curr.second + ds[i];
      if (!check(r, s)) continue;
      if (grid[curr.first][curr.second] + 1 < grid[r][s]) continue;
      dist[r][s] = dist[curr.first][curr.second] + 1;
      Q.push({r, s});
    }
  }

  printf("%d\n", dist[t.first][t.second]);

  return 0;
}
