#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

int pos[2];
int freq[10];

pair<llint, llint> memo[25][25][15][15][2];

pair<llint, llint> rek(int score_a, int score_b, int pos_a, int pos_b, int turn) {
  if (score_a >= 21) return {1LL, 0LL};
  if (score_b >= 21) return {0LL, 1LL};
  if (memo[score_a][score_b][pos_a][pos_b][turn] != make_pair(-1LL, -1LL))
    return memo[score_a][score_b][pos_a][pos_b][turn];

  pair<llint, llint> ret = {0LL, 0LL};
  for (int i = 3; i <= 9; ++i) {
    pair<llint, llint> nxt;
    if (turn == 0) {
      int pa = (pos_a + i) % 10;
      int sa = score_a + pa + 1;
      nxt = rek(sa, score_b, pa, pos_b, 1 - turn);
    } else {
      int pb = (pos_b + i) % 10;
      int sb = score_b + pb + 1;
      nxt = rek(score_a, sb, pos_a, pb, 1 - turn);
    }
    nxt.first *= (llint) freq[i];
    nxt.second *= (llint) freq[i];
    ret.first += nxt.first;
    ret.second += nxt.second;
  }

  return memo[score_a][score_b][pos_a][pos_b][turn] = ret;
}

int main(void) {
  scanf("Player 1 starting position: %d\n", &pos[0]); --pos[0];
  scanf("Player 2 starting position: %d\n", &pos[1]); --pos[1];

  memset(memo, -1, sizeof memo);
  freq[1] = freq[2] = freq[3] = 1;
  for (int k = 0; k < 2; ++k) {
    for (int i = 9; i >= 0; --i) {
      freq[i] = 0;
      if (i - 1 >= 0) freq[i] += freq[i - 1];
      if (i - 2 >= 0) freq[i] += freq[i - 2];
      if (i - 3 >= 0) freq[i] += freq[i - 3];
    }
  }

  auto sol = rek(0, 0, pos[0], pos[1], 0);
  printf("%lld %lld\n", sol.first, sol.second);

  return 0;
}
