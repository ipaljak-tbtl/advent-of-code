#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

set<pair<int, int>> read_dots() {
  set<pair<int, int>> dots;
  int a, b;
  while (scanf("%d,%d", &a, &b) == 2)
    dots.insert({a, b});
  return dots;
}

vector<pair<int, int>> read_folds() {
  vector<pair<int, int>> folds;
  char x;
  int a;
  while (scanf(" fold along %c=%d\n", &x, &a) == 2) {
    assert(x == 'x' || x == 'y');
    folds.push_back({x == 'x'?1:0, a});
  }
  return folds;
}

set<pair<int, int>> fold(const set<pair<int, int>> &dots, pair<int, int> fold) {
  auto [d, a] = fold;
  set<pair<int, int>> result;
  for (auto [x, y] : dots) {
    if (!d)
      swap(x, y);
    if (x == a)
      continue ;
    if (x > a)
      x = a-(x-a) ;
    if (!d)
      swap(x, y);
    result.insert({x, y});
  }
  return result;
}

int main() {
  set<pair<int, int>> dots = read_dots();
  vector<pair<int, int>> folds = read_folds();
  dots = fold(dots, folds[0]);
  printf("%d\n", (int)dots.size());
  return 0;
}
