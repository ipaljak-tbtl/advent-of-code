#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


vector<string> grid;


int count() {
  int m = grid.size();
  int n = grid[0].size();

  int x = -1;
  int y = -1;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      if (grid[i][j] == '^') {
        x = i;
        y = j;
      }
  assert(x != -1 && y != -1);

  int dx = -1;
  int dy = 0;
  int cnt = 0;
  
  while (true) {
    int moved = 0;
    for (int i=0; i<3; i++) {
      int xx = x + dx;
      int yy = y + dy;
      if (xx < 0 || xx >= m || yy < 0 || yy >= n)
        return cnt;
      if (grid[xx][yy] == '#') {
        swap(dx, dy);
        dy = -dy;
        continue ;
      }
      moved = 1;
      x = xx;
      y = yy;
      if (grid[x][y] == '.') {
        grid[x][y] = 'X';
        cnt++;
      }
    }
    assert(moved);
  }

  assert(false);  
}


int main() {
  string line;
  while (cin >> line)
    grid.push_back(line);

  cout << count() << endl;

  return 0;
}
