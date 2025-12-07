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
  while (cin >> line) {
    grid.push_back(line);
  }
  n = (int)grid.size();
  m = (int)grid[0].size();

  int total = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == '@') {
        int count = 0;
        for (int di = -1; di <= 1; di++)
          for (int dj = -1; dj <= 1; dj++) 
            if (di != 0 || dj != 0) {
              int ni = i + di;
              int nj = j + dj;
              if (0 <= ni && ni < n && 0 <= nj && nj < m && grid[ni][nj] == '@')
                count++;
            }
        if (count < 4)
          total++; 
      }

  cout << total << endl;

  return 0;
}
