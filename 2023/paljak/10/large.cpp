#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {-1, 0, 1, 0};

int r, s;
char grid[MAXN][MAXN];
bool in_loop[MAXN][MAXN];

map<char, set<pair<int, int>>> pipes;

inline void init() {
  pipes['-'] = {{0, -1}, {0, 1}};
  pipes['|'] = {{-1, 0}, {1, 0}};
  pipes['L'] = {{-1, 0}, {0, 1}};
  pipes['J'] = {{-1, 0}, {0, -1}};
  pipes['7'] = {{1, 0}, {0, -1}};
  pipes['F'] = {{1, 0}, {0, 1}};
}

inline bool check(pair<int, int> curr) {
  return curr.first >= 0 && curr.first < r && curr.second >= 0 &&
      curr.second < s && grid[curr.first][curr.second] != '.';
}

pair<int, int> next_dir(char pipe_type, pair<int, int> dir) {
  if (pipes[pipe_type].find(dir) == pipes[pipe_type].end())
    return {-1, -1};
  for (auto p : pipes[pipe_type])
    if (p != dir) return p;
  assert(false);
}

int loop_len(pair<int, int> start, pair<int, int> dir, bool draw) {
  pair<int, int> curr = {start.first + dir.first, start.second + dir.second};
  if (draw) in_loop[curr.first][curr.second] = true;
  int ret = 1;
  while (curr != start) {
    if (!check(curr)) return 0;
    dir = next_dir(grid[curr.first][curr.second], {-dir.first, -dir.second});
    if (dir == make_pair(-1, -1)) return 0;
    curr = {curr.first + dir.first, curr.second + dir.second};
    if (draw) in_loop[curr.first][curr.second] = true;
    ++ret;
  }
  return ret;
}

bool check_inside(int i, int j) {
  if (in_loop[i][j]) return false;
  bool ret = false;
  for (int k = j; k < s; ++k) {
    if (!in_loop[i][k]) continue;
    if (grid[i][k] == '-' || grid[i][k] == 'F' || grid[i][k] == '7') continue;
    if (grid[i][k] == 'S') return false;
    ret ^= 1;
  }
  return ret;
}

int main(void) {
  init();
  while (scanf("%s", grid[r++]) == 1);
  --r;
  s = strlen(grid[0]);

  pair<int, int> start;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] == 'S')
        start = {i, j};

  int sol = 0, di = 0;
  for (int i = 0; i < 4; ++i) {
    int len = loop_len(start, {dr[i], ds[i]}, false);
    if (len > sol) {
      sol = len;
      di = i;
    }
  }

  loop_len(start, {dr[di], ds[di]}, true);

  sol = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      sol += check_inside(i, j);

  printf("%d\n", sol);

  return 0;
}
