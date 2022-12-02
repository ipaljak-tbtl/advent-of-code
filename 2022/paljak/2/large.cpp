#include <bits/stdc++.h>

using namespace std;

int main(void) {
  char a, b;
  int score = 0;
  while (scanf("%c %c\n", &a, &b) != EOF) {
    int p2 = a - 'A', p1 = b - 'X' - 1;
    score += (1 + (p1 + p2 + 3) % 3) + (p1 == 0) * 3 + (p1 == 1) * 6;
  }
  printf("%d\n", score);
  return 0;
}
