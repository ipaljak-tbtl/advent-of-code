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
};

int main(void) {
  Paper paper;

  int x, y;
  while (scanf("%d,%d", &x, &y) == 2)
    paper.add_point(x, y);

  char s;
  int k;

  scanf("fold along %c=%d", &s, &k);
  if (s == 'y')
    paper = paper.fold_y(k);
  else
    paper = paper.fold_x(k);

  printf("%d\n", paper.size());

  return 0;
}
