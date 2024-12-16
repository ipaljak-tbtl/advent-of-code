#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef tuple<int, int, int, int> state;
typedef tuple<int, int, int> pos;

const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

int m;
int n;
vector<string> grid;


int dijkstra() {
  int sx = -1;
  int sy = -1;
  int ex = -1;
  int ey = -1;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      if (grid[i][j] == 'S')
        sx = i, sy = j;
      else if (grid[i][j] == 'E')
        ex = i, ey = j;

  int min_path = -1;
  priority_queue<state, vector<state>, greater<state>> q;
  map<pos, int> dist_s;
  q.push({0, sx, sy, 0});

  while (!q.empty()) {
    auto [c, x, y, d] = q.top();
    q.pop();
    if (dist_s.count({x, y, d}))
      continue;
    dist_s[{x, y, d}] = c;
    if (x == ex && y == ey && min_path == -1) {
      min_path = c;
      continue ;
    }
    int xx = x+DX[d];
    int yy = y+DY[d];
    if (xx >= 0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] != '#')
      q.push({c+1, xx, yy, d});
    q.push({c+1000, x, y, (d+1)%4});
    q.push({c+1000, x, y, (d+3)%4});
  }
  assert(min_path != -1);

  for (int i=0; i<4; i++)
    q.push({0, ex, ey, i});
  map<pos, int> dist_e;

  while (!q.empty()) {
    auto [c, x, y, d] = q.top();
    q.pop();
    if (dist_e.count({x, y, d}))
      continue;
    dist_e[{x, y, d}] = c;
    if (x == sx && y == sy)
      continue ;
    int xx = x-DX[d];
    int yy = y-DY[d];
    if (xx >= 0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] != '#')
      q.push({c+1, xx, yy, d});
    q.push({c+1000, x, y, (d+1)%4});
    q.push({c+1000, x, y, (d+3)%4});
  }

  set<pair<int, int>> all;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      for (int d=0; d<4; d++)
        if (dist_s.count({i, j, d}) && dist_e.count({i, j, d}))
          if (dist_s[{i, j, d}]+dist_e[{i, j, d}] == min_path) {
          grid[i][j] = 'O';
          all.insert({i, j});
        }
  
  for (auto s : grid)
    cout << s << endl;

  return all.size();
}

int main() {
  string line;
  while (cin >> line) {
    grid.push_back(line);
  }
  m = grid.size();
  n = grid[0].size();

  cout << dijkstra() << endl;
}
