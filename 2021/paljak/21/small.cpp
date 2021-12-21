#include <bits/stdc++.h>

using namespace std;

int pos[2];
int score[2];

int main(void) {
  scanf("Player 1 starting position: %d\n", &pos[0]); --pos[0];
  scanf("Player 2 starting position: %d\n", &pos[1]); --pos[1];

  int die = 0, rolls = 0;
  for (int turn = 0; ; turn = 1 - turn) {
    for (int i = 0; i < 3; ++i) {
      pos[turn] = (pos[turn] + die + 1) % 10;
      die = (die + 1) % 100;
    }
    rolls += 3;
    score[turn] += 1 + pos[turn];
    if (score[turn] >= 1000) break;
  }

  printf("%d\n", rolls * min(score[0], score[1]));
  return 0;
}
