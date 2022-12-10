#include <bits/stdc++.h>

using namespace std;

char grid[7][41];
int x[250];

int main(void) {
  string cmd;
  int cycle = 0;
  x[0] = 1;
  while (cin >> cmd) {
    if (cmd == "noop") {
      ++cycle;
      x[cycle] = x[cycle - 1];
    } else {
      cycle += 2;
      x[cycle] = x[cycle - 1] = x[cycle - 2];
      int dx;
      cin >> dx;
      x[cycle] += dx;
    }
  }

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 40; ++j) {
      if (abs(j - x[i * 40 + j]) <= 1) printf("#"); else printf(".");
    }
    printf("\n");
  }

  return 0;
}
