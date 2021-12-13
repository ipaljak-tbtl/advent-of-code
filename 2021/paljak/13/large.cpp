#include <bits/stdc++.h>

using namespace std;

struct Paper {
  set<pair<int, int>> points;

  Paper() {}

  int size() {
    return points.size();
  }

  void add_point(int x, int y) {
    points.insert({x, y});
  }

  Paper fold_x(int x) {
    Paper new_paper;
    for (auto &p : points) {
      if (p.first < x) new_paper.add_point(p.first, p.second);
      if (p.first > x) new_paper.add_point(2 * x - p.first, p.second);
    }
    return new_paper;
  }

  Paper fold_y(int y) {
    Paper new_paper;
    for (auto &p : points) {
      if (p.second < y) new_paper.add_point(p.first, p.second);
      if (p.second > y) new_paper.add_point(p.first, 2 * y - p.second);
    }
    return new_paper;
  }

  void print() {
    char grid[15][55];
    memset(grid, '.', sizeof grid);
    for (auto &p : points)
      grid[p.second][p.first] = '#';
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 50; ++j)
        printf("%c", grid[i][j]);
      printf("\n");
    }
  }
};

int main(void) {
  Paper paper;

  int x, y;
  while (scanf("%d,%d", &x, &y) == 2)
    paper.add_point(x, y);

  char s;
  int k;
  while (scanf("fold along %c=%d\n", &s, &k) == 2) {
    if (s == 'y')
      paper = paper.fold_y(k);
    else
      paper = paper.fold_x(k);
  }

  paper.print();
  return 0;
}
