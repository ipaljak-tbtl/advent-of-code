#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

int m;
int n;
vector<string> grid;
vector<vector<int>> done;

typedef pair<int, int> point;
typedef pair<point, point> edge;


int consecutive(const edge &a, const edge &b) {
  if (  a.second != b.first && b.second != a.first) 
    return 0;
  int dx1 = abs(a.first.first-a.second.first);
  int dy1 = abs(a.first.second-a.second.second);
  int dx2 = abs(b.first.first-b.second.first);
  int dy2 = abs(b.first.second-b.second.second);
  return (dx1 == dx2 && dy1 == dy2);
}


int count_lines(const vector<edge> &edges) {
  int total = edges.size();
  for (int i=0; i<(int)edges.size(); i++)
    for (int j=i+1; j<(int)edges.size(); j++)
      if (consecutive(edges[i], edges[j]))
        total--;
  return total;
}


pair<int, vector<edge>> dfs(int x, int y) {
  done[x][y] = 1;
  int a = 1;
  vector<edge> p;
  for (int d=0; d<4; d++) {
    int x2 = x + DX[d];
    int y2 = y + DY[d];
    if (x2 < 0 || x2 >= m || y2 < 0 || y2 >= n || grid[x2][y2] != grid[x][y]) {
      int ox = DY[d];
      int oy = -DX[d];
      edge e = {{2*x+DX[d]-ox, 2*y+DY[d]-oy}, {2*x+DX[d]+ox, 2*y+DY[d]+oy}};
      p.push_back(e);
      continue;
    }
    if (done[x2][y2])
      continue;
    auto [a2, p2] = dfs(x2, y2);
    a += a2;
    for (auto x : p2)
      p.push_back(x);
  }
  return {a, p};
}


int main() {
  string line;
  while (cin >> line)
    grid.push_back(line);

  m = grid.size();
  n = grid[0].size();
  done = vector<vector<int>>(m, vector<int>(n, 0));
  llint total = 0;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      if (!done[i][j]) {
        auto [a, p] = dfs(i, j);
        int lines = count_lines(p);
        total += a*lines;
      }
  cout << total << endl;
  return 0;
}