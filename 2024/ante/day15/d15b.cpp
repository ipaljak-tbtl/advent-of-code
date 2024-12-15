#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


const map<char, pair<int, int>> DIR = {
  {'^', {-1, 0}},
  {'v', {1, 0}}, 
  {'<', {0, -1}},
  {'>', {0, 1}}
};

const map<char, string> TILE = {
  {'#', "##"},
  {'O', "[]"},
  {'.', ".."},
  {'@', "@."}
};


int m;
int n;
vector<string> grid;
string moves;
int px;
int py;


void move_hor(const char c) {
  auto [dx, dy] = DIR.at(c);
  for (int x=px+dx, y=py+dy, cnt=1; ; x+=dx, y+=dy, cnt++) {
    if (x < 0 || x >= m || y < 0 || y >= n)
      return ;
    if (grid[x][y] == '#')
      return ;
    if (grid[x][y] == '.') {
      for (int i=cnt; i>0; i--)
        grid[px+i*dx][py+i*dy] = grid[px+(i-1)*dx][py+(i-1)*dy];
      grid[px][py] = '.';
      px += dx;
      py += dy;
      grid[px][py] = '@';
      return ;
    }
    assert(grid[x][y] == '[' || grid[x][y] == ']');
  }
  assert(false);
}


int move_ver(const char c, int px, int py, vector<string> &grid) {
  auto [dx, dy] = DIR.at(c);
  int xx = px+dx;
  int yy = py+dy;
  if (xx < 0 || xx >= m || yy < 0 || yy >= n)
    return 0;
  if (grid[xx][yy] == '#')
    return 0;
  if (grid[xx][yy] == '.') {
    swap(grid[px][py], grid[xx][yy]);
    return 1;
  }

  assert(grid[xx][yy] == '[' || grid[xx][yy] == ']');
  int oy = grid[xx][yy] == '[' ? yy+1 : yy-1;

  vector<string> old_grid = grid;
  if (!move_ver(c, xx, yy, grid)) {
    grid = old_grid;
    return 0;
  }
  if (!move_ver(c, xx, oy, grid)) {
    grid = old_grid;
    return 0;
  }

  swap(grid[px][py], grid[xx][yy]);
  return 1;
}


void move(const char c) {
  if (c == 'v' || c == '^') {
    if (move_ver(c, px, py, grid)) {
      px += DIR.at(c).first;
      py += DIR.at(c).second;
    }
  }
  else {
    move_hor(c);
  }
}


int score() {
  int ans = 0;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      if (grid[i][j] == '[')
        ans += 100*i+j;
  return ans;
}


void display() {
  for (auto row : grid)
    cout << row << endl;
  cout << endl;
}

int main() {
  string line;
  while (cin >> line) {
    if (line.size() > 0 && line[0] == '#') {
      string row;
      for (auto c : line)
        row += TILE.at(c);
      grid.push_back(row);
    }
    else
      moves += line;
  }

  m = grid.size();
  n = grid[0].size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '@') {
        px = i;
        py = j;
      }
    }
  }

  for (auto c : moves) {
    move(c);
  }

  cout << score() << endl;
}
