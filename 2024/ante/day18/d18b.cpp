#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


const int SIZE = 71;
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

vector<int> x;
vector<int> y;


int bfs(int count) {
  int grid[SIZE][SIZE];
  memset(grid, 0, sizeof grid);

  for (int i=0; i<count && i<(int)x.size(); i++)
    grid[y[i]][x[i]] = 1;

  queue<pair<int, int>> Q;
  int dist[SIZE][SIZE];
  memset(dist, -1, sizeof dist);

  Q.push({0, 0});
  dist[0][0] = 0;

  while (!Q.empty()) {
    auto [r, c] = Q.front(); Q.pop();
    if (r == SIZE-1 && c == SIZE-1)
      return dist[r][c];

    for (int d=0; d<4; d++) {
      int nr = r + DY[d];
      int nc = c + DX[d];
      if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE)
        continue;
      if (grid[nr][nc] == 1)
        continue;
      if (dist[nr][nc] != -1)
        continue;
      dist[nr][nc] = dist[r][c] + 1;
      Q.push({nr, nc});
    }
  }
  return -1;
}


int find_first() {
  for (int i=0; i<=(int)x.size(); i++) {
    int ret = bfs(i);
    TRACE(i _ x[i] _ y[i] _ ret);
    if (bfs(i) == -1)
      return i;
  }
  assert(false);
}


int main() {
  int a, b;
  while (scanf("%d,%d", &a, &b) == 2) {
    x.push_back(a);
    y.push_back(b);
  }

  int first = find_first();
  cout << x[first-1] << "," << y[first-1] << endl;
  return 0;
}
