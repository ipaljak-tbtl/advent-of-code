#include <bits/stdc++.h>

using namespace std;

int main(void) {
  int l1, r1, l2, r2;
  int sol = 0;
  while (scanf("%d-%d,%d-%d", &l1, &r1, &l2, &r2) != EOF)
    sol += !(r1 < l2 || r2 < l1);
  printf("%d\n", sol);
  return 0;
}
