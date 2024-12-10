#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int m;
int n;
vector<string> grid;
vector<vector<int>> done;


int dfs(int x, int y, int t) {
  if (x < 0 || x >= m || y < 0 || y >= n)
    return 0;
  if (grid[x][y] != '0'+t)
    return 0;
  if (done[x][y] != -1)
    return done[x][y];;
  if (grid[x][y] == '9')
    return 1;
  int res = 0;
  res += dfs(x-1, y, t+1);
  res += dfs(x+1, y, t+1);
  res += dfs(x, y-1, t+1);
  res += dfs(x, y+1, t+1);
  return done[x][y] = res;
}


int count(int x, int y) {
  done = vector<vector<int>>(m, vector<int>(n, -1));
  return dfs(x, y, 0);
}

int main() {
  string line;
  while (cin >> line) 
    grid.push_back(line);
  m = grid.size();
  n = grid[0].size();

  int total = 0;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      total += count(i, j);
  cout << total << endl;

  return 0;
}
