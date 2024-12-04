#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


const string TARGET = "XMAS";

int m;
int n;
vector<string> grid;


int find(int x, int y, int dx, int dy) {
  for (int i=0; i<(int)TARGET.size(); i++, x+=dx, y+=dy) {
    if (x < 0 || x >= m || y < 0 || y >= n)
      return 0;
    if (grid[x][y] != TARGET[i])
      return 0;
  }
  return 1;
}


int main() {
  string s;
  while (cin >> s)
    grid.push_back(s);
  m = grid.size();
  n = grid[0].size();

  int total = 0;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      for (int dx=-1; dx<=1; dx++)
        for (int dy=-1; dy<=1; dy++)
          if ((dx != 0 || dy !=0 ) && find(i, j, dx, dy))
            total++;

  cout << total << endl;
  return 0;
}
