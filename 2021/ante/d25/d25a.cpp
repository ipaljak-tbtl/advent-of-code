#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int n;
int m;
vector<string> g;
set<pair<int, int>> hor;
set<pair<int, int>> ver;

void read_input() {
  string s;
  while (cin >> s)
    g.push_back(s);
  n = g.size();
  m = g[0].size();
}

void init_herds() {
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++) {
      if (g[i][j] == '>' && g[i][(j+1)%m] == '.')
        hor.insert({i, j});
      if (g[i][j] == 'v' && g[(i+1)%n][j] == '.')
        ver.insert({i, j});
    }
}

void update() {
  set<pair<int, int>> nhor;
  set<pair<int, int>> nver;
  for (auto [x, y] : hor)
    for (int dx = -2; dx <= 2; dx++)
      for (int dy = -2; dy <= 2; dy++) {
        int i = (x+dx+n)%n;
        int j = (y+dy+m)%m;
        if (g[i][j] == '>' && g[i][(j+1)%m] == '.')
          nhor.insert({i, j});
        if (g[i][j] == 'v' && g[(i+1)%n][j] == '.')
          nver.insert({i, j});
      }
  for (auto [x, y] : ver)
    for (int dx = -2; dx <= 2; dx++)
      for (int dy = -2; dy <= 2; dy++) {
        int i = (x+dx+n)%n;
        int j = (y+dy+m)%m;
        if (g[i][j] == '>' && g[i][(j+1)%m] == '.')
          nhor.insert({i, j});
        if (g[i][j] == 'v' && g[(i+1)%n][j] == '.')
          nver.insert({i, j});
      }
  swap(nhor, hor);
  swap(nver, ver);
}

int step() {
  if (hor.empty() && ver.empty())
    return 0;
  for (auto [x, y] : hor) {
    int y1 = (y+1)%m;
    assert(g[x][y1] == '.');
    g[x][y1] = '>';
    g[x][y] = '.';
    int x1 = (x-1+n)%n;
    if (g[x1][y] == 'v')
      ver.insert({x1, y});
  }
  for (auto [x, y] : ver) {
    int x1 = (x+1)%n;
    if (g[x1][y] != '.')
      continue ;
    g[x1][y] = 'v';
    g[x][y] = '.';
  }
  update();
  return 1;
}

int main() {
  read_input();
  init_herds();
  int steps = 0;
  while (step())
    steps++;
  cout << steps+1 << endl;
  return 0;
}
