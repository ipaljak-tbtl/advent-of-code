#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

int n;
int m;
vector<string> grid;

int main() {
  string line;
  while (cin >> line)
    grid.push_back(line);
  
  n = (int)grid.size();
  m = (int)grid[0].size();
  llint cnt[n][m];
  memset(cnt, 0, sizeof(cnt));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'S')
        grid[i][j] = '|', cnt[i][j] = 1;

  for (int i = 1; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] != '^' && grid[i-1][j] == '|')
        grid[i][j] = '|', cnt[i][j] += cnt[i-1][j];
      else if (grid[i][j] == '^' && grid[i-1][j] == '|') {
        if (j > 0)
          grid[i][j-1] = '|', cnt[i][j-1] += cnt[i-1][j];
        if (j < m-1)
          grid[i][j+1] = '|', cnt[i][j+1] += cnt[i-1][j];
      }

  llint total = 0;
  for (int i = 0; i < m; i++)
    total += cnt[n-1][i];
  cout << total << endl;

  return 0;
}
