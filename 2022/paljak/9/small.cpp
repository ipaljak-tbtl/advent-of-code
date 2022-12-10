#include <bits/stdc++.h>

using namespace std;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

pair<int, int> h, t;

char s[2];
int d;

set<pair<int, int>> visited;

int d_id(char dir) {
  if (dir == 'R') return 0;
  if (dir == 'U') return 1;
  if (dir == 'L') return 2;
  if (dir == 'D') return 3;
  assert(false);
}

void go(int dir, int d) {
  visited.insert(t);
  for (int i = 0; i < d; ++i) {
    h.first += dr[dir];
    h.second += ds[dir];
    if (abs(h.first - t.first) == 2) {
      t.first += (h.first - t.first) / abs(h.first - t.first);
      t.second = h.second;
    }
    if (abs(h.second - t.second) == 2) {
      t.second += (h.second - t.second) / abs(h.second - t.second);
      t.first = h.first;
    }
    visited.insert(t);
  }
}

int main(void) {
  while (scanf("%s %d", s, &d) != EOF)
    go(d_id(s[0]), d);

  printf("%d\n", (int)visited.size());
  return 0;
}
