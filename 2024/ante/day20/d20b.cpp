#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};


vector<vector<int>> bfs(vector<string> grid, int sx, int sy) {
  int m = grid.size();
  int n = grid[0].size();

  queue<pair<int, int>> Q;
  vector<vector<int>> dist(m, vector<int>(n, -1));

  Q.push({sx, sy});
  dist[sx][sy] = 0;

  while (!Q.empty()) {
    auto [r, c] = Q.front(); Q.pop();

    for (int d=0; d<4; d++) {
      int nr = r + DY[d];
      int nc = c + DX[d];
      if (nr < 0 || nr >= m || nc < 0 || nc >= n)
        continue;
      if (grid[nr][nc] == '#')
        continue;
      if (dist[nr][nc] != -1)
        continue;
      dist[nr][nc] = dist[r][c] + 1;
      Q.push({nr, nc});
    }
  }

  return dist;
}


int main() {
  string line;
  vector<string> grid;
  while (cin >> line)
    grid.push_back(line);

  int m = grid.size();
  int n = grid[0].size();
  int sx = -1;
  int sy = -1;
  int ex = -1;
  int ey = -1;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (grid[i][j] == 'S')
        sx = i, sy = j;
      else if (grid[i][j] == 'E')
        ex = i, ey = j;

  auto dist_start = bfs(grid, sx, sy);
  auto dist_end = bfs(grid, ex, ey);
  int best_path = dist_start[ex][ey];

  TRACE(best_path);

  map<int, int> hist;
  int count = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        if (dist_start[i][j] != -1)
          for (int ii=0; ii < m; ii++)
            for (int jj=0; jj < n; jj++) {
              int dist = abs(i-ii)+abs(j-jj);
              if (dist == 0 || dist > 20)
                continue ;
              if (dist_end[ii][jj] == -1)
                continue ;
              int len = dist_start[i][j] + dist + dist_end[ii][jj];
              if (len+100 <= best_path)
                count++;
              hist[best_path-len]++;
            }

  cout << count << endl;

  return 0;
}
