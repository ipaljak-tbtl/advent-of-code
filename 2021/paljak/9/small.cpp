#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;

const int dr[] = {0, 1, -1, 0};
const int ds[] = {1, 0, 0, -1};

int r, s;
char grid[MAXN][MAXN];

bool inside(int i, int j) {
  return i >= 0 && i < r && j >= 0 && j < s;
}

int main(void) {
  while (scanf("%s", grid[r]) == 1) ++r;
  s = strlen(grid[0]);

  int sol = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      bool low = true;
      for (int k = 0; k < 4; ++k) {
        int ii = i + dr[k], jj = j + ds[k];
        if (!inside(ii, jj)) continue;
        low &= grid[ii][jj] > grid[i][j];
      }
      if (low) sol += 1 + (grid[i][j] - '0');
    }
  }

  printf("%d\n", sol);
  return 0;
}
