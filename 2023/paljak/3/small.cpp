#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

const int dr[] = {0, -1, -1, -1, 0, 1, 1, 1};
const int ds[] = {-1, -1, 0, 1, 1, 1, 0, -1};

char grid[MAXN][MAXN];

int r, s;
int val[MAXN][MAXN];

inline bool check(int i, int j) {
  return i >= 0 && i < r && j >= 0 && j < s && val[i][j] != 0;
}

void remove(int i, int j) {
  assert(val[i][j] != 0);
  for (int k = j; k < s && val[i][k] != 0; ++k)
    val[i][k] = 0;
  for (int k = j - 1; k >= 0 && val[i][k] != 0; --k)
    val[i][k] = 0;
}

void calc_vals() {
  for (int i = 0; i < r; ++i) {
    int curr = 0;
    for (int j = 0; j < s; ++j) {
      if (grid[i][j] < '0' || grid[i][j] > '9')
        curr = 0;
      else
        curr = curr * 10 + grid[i][j] - '0';
      val[i][j] = curr;
    }
    for (int j = s - 2; j >= 0; --j)
      if (val[i][j] != 0 && val[i][j + 1] > val[i][j])
        val[i][j] = val[i][j + 1];
  }
}

int main(void) {
  while (scanf("%s", grid[r++]) == 1);
  --r;
  s = strlen(grid[0]);

  calc_vals();

  int sol = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (grid[i][j] == '.' || (grid[i][j] >= '0' && grid[i][j] <= '9'))
        continue;
      for (int k = 0; k < 8; ++k) {
        int rr = i + dr[k], ss = j + ds[k];
        if (check(rr, ss)) {
          sol += val[rr][ss];
          remove(rr, ss);
        }
      }
    }
  }

  printf("%d\n", sol);

  return 0;
}
