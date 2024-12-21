#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};


int bfs(vector<string> grid, int sx, int sy, int ex, int ey) {
  int m = grid.size();
  int n = grid[0].size();

  queue<pair<int, int>> Q;
  int dist[m][n];
  memset(dist, -1, sizeof dist);

  Q.push({sx, sy});
  dist[sx][sy] = 0;

  while (!Q.empty()) {
    auto [r, c] = Q.front(); Q.pop();
    if (r == ex && c == ey)
      return dist[r][c];

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
  return -1;
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

  int best_path = bfs(grid, sx, sy, ex, ey);
  TRACE(best_path);

  map<int, int> hist;
  int count = 0;
  for (int d = 0; d < 4; d++)
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) {
        int ii = i+DX[d];
        int jj = j+DY[d];
        if (ii < 0 || ii >= m || jj < 0 || jj >= n)
          continue ;
        if (grid[ii][jj] == '#')
          continue ;

        char a = grid[i][j];
        grid[i][j] = '.';
        int d1 = bfs(grid, sx, sy, i, j);
        grid[i][j] = a;

        char aa = grid[ii][jj];
        grid[ii][jj] = '.';
        int d2 = bfs(grid, ii, jj, ex, ey);
        grid[ii][jj] = aa;  

        if (d1 != -1 && d2 != -1) {
          int len = d1 + d2 + 1;
          if (len+100 <= best_path)
            count++;
          hist[best_path-len]++;
        }

      }

  cout << count << endl;

  return 0;
}
