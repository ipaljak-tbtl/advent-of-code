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

int m;
int n;
vector<string> grid;
string moves;
int px;
int py;


void move(const char c) {
  auto [dx, dy] = DIR.at(c);
  int pushes = false;
  for (int x=px+dx, y=py+dy; ; x+=dx, y+=dy) {
    if (x < 0 || x >= m || y < 0 || y >= n)
      return ;
    if (grid[x][y] == '#')
      return ;
    if (grid[x][y] == '.') {
      if (pushes)
        grid[x][y] ='O';
      grid[px][py] = '.';
      px += dx;
      py += dy;
      grid[px][py] = '@';
      return ;
    }
    assert(grid[x][y] == 'O');
    pushes = true;
  }
  assert(false);
}


int score() {
  int ans = 0;
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      if (grid[i][j] == 'O')
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
    if (line.size() > 0 && line[0] == '#')
      grid.push_back(line);
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
