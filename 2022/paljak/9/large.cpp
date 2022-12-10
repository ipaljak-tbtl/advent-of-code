#include <bits/stdc++.h>

using namespace std;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

char s[2];
int d;

pair<int, int> rope[11];

set<pair<int, int>> visited;

int d_id(char dir) {
  if (dir == 'R') return 0;
  if (dir == 'U') return 1;
  if (dir == 'L') return 2;
  if (dir == 'D') return 3;
  assert(false);
}

void go(int dir, int d) {
  for (int i = 0; i < d; ++i) {
    rope[0].first += dr[dir];
    rope[0].second += ds[dir];
    for (int j = 0; j < 9; ++j) {
      int _dx = rope[j].first - rope[j + 1].first, _dy = rope[j].second - rope[j + 1].second;
      if (_dx * _dx + _dy * _dy <= 2) continue;
      if (_dx != 0) rope[j + 1].first += _dx / abs(_dx);
      if (_dy != 0) rope[j + 1].second += _dy / abs(_dy);
    }
    visited.insert(rope[9]);
  }
}

int main(void) {
  while (scanf("%s %d", s, &d) != EOF)
    go(d_id(s[0]), d);

  printf("%d\n", (int)visited.size());
  return 0;
}
