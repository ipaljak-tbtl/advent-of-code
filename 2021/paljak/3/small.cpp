#include <bits/stdc++.h>

using namespace std;

const int MAXB = 12;

char gam[MAXB], eps[MAXB];

int n;
int popcount[MAXB];

int dec(const char *b) {
  int ret = 0;
  for (int i = 0; i < MAXB; ++i, ret <<= 1)
    ret += b[i] == '1';
  return ret >> 1;
}

int main(void) {
  char b[MAXB];
  while (scanf("%s", b) != EOF) {
    ++n;
    for (int i = 0; i < MAXB; ++i)
      popcount[i] += b[i] == '1';
  }

  for (int i = 0; i < MAXB; ++i) {
    gam[i] = '1';
    eps[i] = '0';
    if (2 * popcount[i] < n)
      swap(gam[i], eps[i]);
  }

  printf("%d\n", dec(gam) * dec(eps));

  return 0;
}
