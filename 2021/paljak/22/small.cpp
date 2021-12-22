#include <bits/stdc++.h>

using namespace std;

int cube[110][110][110];

int main(void) {
  char s[5];
  int x1, x2, y1, y2, z1, z2;
  while (scanf("%s x=%d..%d,y=%d..%d,z=%d..%d", s, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    if (z1 > z2) swap(z1, z2);

    if (abs(x1) > 50 || abs(x2) > 50 ||
        abs(y1) > 50 || abs(y2) > 50 ||
        abs(z1) > 50 || abs(z2) > 50)
      continue;

     for (int i = x1 + 50; i <= x2 + 50; ++i)
       for (int j = y1 + 50; j <= y2 + 50; ++j)
         for (int k = z1 + 50; k <= z2 + 50; ++k)
           if (s[1] == 'n')
             cube[i][j][k] = 1;
           else
             cube[i][j][k] = 0;
  }

  int sol = 0;
  for (int i = 0; i <= 100; ++i)
    for (int j = 0; j <= 100; ++j)
      for (int k = 0; k <= 100; ++k)
        sol += cube[i][j][k];

  printf("%d\n", sol);
  return 0;
}
