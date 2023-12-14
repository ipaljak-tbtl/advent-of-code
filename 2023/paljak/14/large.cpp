#include <bits/stdc++.h>

using namespace std;

const int CYCLES = 1000000000;
const int MAXN = 150;
const int P = 31;
const int MOD = 1e9 + 7;

int r, s;
char grid[MAXN][MAXN];

inline bool check(int i, int j) {
  return i >= 0 && i < r && j >= 0 && j < s;
}

inline int add(int a, int b) {
  if (a + b < 0) return a + b + MOD;
  if (a + b >= MOD) return a + b - MOD;
  return a + b;
}

inline int mul(int a, int b) {
  return (long long) a * b % MOD;
}

int grid_hash() {
  int ret = 1;
  int x = 1;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      x = mul(x, P);
      ret = add(ret, mul(x, (int) grid[i][j]));
    }
  }
  return ret;
}

void rotate() {
  for (int i = 0; i < r; ++i)
    for (int j = i; j < s; ++j)
      swap(grid[i][j], grid[j][i]);

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s / 2; ++j)
      swap(grid[i][j], grid[i][s - j - 1]);
}

void cycle() {
  for (int dir = 0; dir < 4; ++dir, rotate()) {
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < s; ++j) {
        if (grid[i][j] != 'O') continue;
        int k = i - 1;
        while (k >= 0 && grid[k][j] == '.') {
          grid[k][j] = 'O';
          grid[k + 1][j] = '.';
          --k;
        }
      }
    }
  }
}

int main(void) {
  while (scanf("%s", grid[r++]) == 1);
  --r;
  s = strlen(grid[0]);

  map<int, int> m;
  m[grid_hash()] = 0;

  int rem;
  for (int it = 0; ; ++it) {
    cycle();
    int h = grid_hash();
    if (m.find(h) == m.end()) {
      m[h] = it;
      continue;
    }
    rem = (CYCLES - it) % (it - m[h]);
    break;
  }

  for (int i = 0; i < rem - 1; ++i)
    cycle();

  int sol = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      sol += (grid[i][j] == 'O') * (r - i);

  printf("%d\n", sol);
  return 0;
}
