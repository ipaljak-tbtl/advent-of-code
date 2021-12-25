#include <bits/stdc++.h>

using namespace std;

int r, s;
char grid[150][150];

set<pair<int, int>> rt, bk;

inline void init() {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (grid[i][j] == '>') rt.insert({i, j});
      if (grid[i][j] == 'v') bk.insert({i, j});
    }
  }
}

int main(void) {
  while (scanf("%s", grid[r]) == 1) {
    s = strlen(grid[r]);
    ++r;
  }

  init();

  int step = 0;
  bool move = false;
  do {
    set<pair<int, int>> _rt, _bk;
    move = false;

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < s; ++j) {
        if (grid[i][j] != '>') continue;
        int ii = i, jj = (j + 1) % s;
        if (rt.find({ii, jj}) == rt.end() && bk.find({ii, jj}) == bk.end()) {
          _rt.insert({ii, jj});
          move = true;
        } else {
          _rt.insert({i, j});
        }
      }
    }

    rt = _rt;

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < s; ++j) {
        if (grid[i][j] != 'v') continue;
        int ii = (i + 1) % r, jj = j;
        if (rt.find({ii, jj}) == rt.end() && bk.find({ii, jj}) == bk.end()) {
          _bk.insert({ii, jj});
          move = true;
        } else {
          _bk.insert({i, j});
        }
      }
    }

    bk = _bk;
    ++step;

    //printf("Step #%d\n", step);
    //for (int i = 0; i < r; ++i) {
      //for (int j = 0; j < s; ++j) {
        //grid[i][j] = '.';
        //if (rt.find({i, j}) != rt.end()) grid[i][j] = '>';
        //if (bk.find({i, j}) != bk.end()) grid[i][j] = 'v';
      //}
      //printf("%s\n", grid[i]);
    //}

  } while (move);

  printf("%d\n", step);
  return 0;
}
