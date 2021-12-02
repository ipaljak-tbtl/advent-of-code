#include <bits/stdc++.h>

using namespace std;

int x, y;

int main(void) {
  char dir[15];
  int val;

  while (scanf("%s%d", dir, &val) != EOF) {
    if (dir[0] == 'f') x += val;
    if (dir[0] == 'd') y += val;
    if (dir[0] == 'u') y -= val;
  }

  printf("%d\n", x * y);
}
