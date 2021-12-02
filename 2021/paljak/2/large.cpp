#include <bits/stdc++.h>

using namespace std;

int x, y, aim;

int main(void) {
  char dir[15];
  int val;

  while (scanf("%s%d", dir, &val) != EOF) {
    if (dir[0] == 'f') x += val, y += aim * val;
    if (dir[0] == 'd') aim += val;
    if (dir[0] == 'u') aim -= val;
  }

  printf("%d\n", x * y);
}
