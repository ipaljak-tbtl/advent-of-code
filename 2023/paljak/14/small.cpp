#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

int r, s;
char grid[MAXN][MAXN];

int main(void) {
  while (scanf("%s", grid[r++]) == 1);
  --r;
  s = strlen(grid[0]);

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

  int sol = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      sol += (grid[i][j] == 'O') * (r - i);

  printf("%d\n", sol);
  return 0;
}
