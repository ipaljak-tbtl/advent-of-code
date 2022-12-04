#include <bits/stdc++.h>

using namespace std;

int main(void) {
  int l1, r1, l2, r2;
  int sol = 0;
  while (scanf("%d-%d,%d-%d", &l1, &r1, &l2, &r2) != EOF)
    sol += (l1 >= l2 && r1 <= r2) || (l2 >= l1 && r2 <= r1);
  printf("%d\n", sol);
  return 0;
}
