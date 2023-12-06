#include <bits/stdc++.h>

using namespace std;

const int N = 4;

int t[N + 1], d[N + 1];
char dummy[10];

int ways(int i) {
  int ret = 0;
  for (int s = 0; s < t[i]; ++s) {
    int dist = (t[i] - s) * s;
    ret += dist > d[i];
  }
  return ret;
}

int main(void) {
  scanf("%s%d%d%d%d", dummy, &t[0], &t[1], &t[2], &t[3]);
  scanf("%s%d%d%d%d", dummy, &d[0], &d[1], &d[2], &d[3]);

  int sol = 1;
  for (int i = 0; i < 4; ++i)
    sol *= ways(i);

  printf("%d\n", sol);

  return 0;
}
