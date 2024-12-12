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


pair<int, int> dfs(int x, int y) {
  done[x][y] = 1;
  int a = 1;
  int p = 0;
  for (int d=0; d<4; d++) {
    int x2 = x + DX[d];
    int y2 = y + DY[d];
    if (x2 < 0 || x2 >= m || y2 < 0 || y2 >= n) {
      p++;
      continue;
    }
    if (grid[x2][y2] != grid[x][y]) {
      p++;
      continue;
    }
    if (done[x2][y2])
      continue;
    auto [a2, p2] = dfs(x2, y2);
    a += a2;
    p += p2;
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
        total += a*p;
      }
  cout << total << endl;
  return 0;
}
