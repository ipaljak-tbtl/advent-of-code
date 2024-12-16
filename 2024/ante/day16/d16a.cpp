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

  priority_queue<state, vector<state>, greater<state>> q;
  set<pos> done;

  q.push({0, sx, sy, 0});

  while (!q.empty()) {
    auto [c, x, y, d] = q.top();
    q.pop();

    if (done.count({x, y, d}))
      continue;
    done.insert({x, y, d});

    if (x == ex && y == ey)
      return c;

    int xx = x+DX[d];
    int yy = y+DY[d];
    if (xx >= 0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] != '#')
      q.push({c+1, xx, yy, d});

    q.push({c+1000, x, y, (d+1)%4});
    q.push({c+1000, x, y, (d+3)%4});
  }

  assert(false);
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
