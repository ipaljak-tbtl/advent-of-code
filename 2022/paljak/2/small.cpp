#include <bits/stdc++.h>

using namespace std;

int main(void) {
  char a, b;
  int score = 0;
  while (scanf("%c %c\n", &a, &b) != EOF) {
    int p2 = a - 'A', p1 = b - 'X';
    score += p1 + 1 + (p1 == p2) * 3 + (p1 == (p2 + 1) % 3) * 6;
  }
  printf("%d\n", score);
  return 0;
}
