#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


int count(const vector<string>& grid) {
  int m = grid.size();
  int n = grid[0].size();

  map<char, set<pair<int, int>>> antennas;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (grid[i][j] != '.')
        antennas[grid[i][j]].insert({i, j});

  set<pair<int, int>> antinodes;
  for (auto& [antenna, pos] : antennas)
    for (auto& [x1, y1] : pos) 
      for (auto& [x2, y2] : pos) {
        if (x1 == x2 && y1 == y2)
          continue;
        int xx = x1;
        int yy = y1;
        while (xx >= 0 && xx < m && yy >= 0 && yy < n) {
          antinodes.insert({xx, yy});
          xx += (x1 - x2);
          yy += (y1 - y2);
        }
      }

  return antinodes.size();
}


int main() {
  vector<string> grid;
  string line;
  while (cin >> line)
    grid.push_back(line);

  cout << count(grid) << endl;
  return 0;
}
