#include <bits/stdc++.h>

using namespace std;

long long memo[260][10];

vector<int> v;

void parse_nums() {
  string s;
  cin >> s;
  int curr = 0;
  for (const char c : s) {
    if (c == ',') {
      v.push_back(curr);
      curr = 0;
      continue;
    }
    curr *= 10;
    curr += c - '0';
  }
  v.push_back(curr);
}

long long dp(int i, int j) {
  if (memo[i][j] != -1) return memo[i][j];
  if (i == 0) return memo[i][j] = 1LL;
  if (j != 0)
    return memo[i][j] = dp(i - 1, j - 1);
  else
    return memo[i][j] = dp(i - 1, 6) + dp(i - 1, 8);
}

int main(void) {
  parse_nums();

  memset(memo, -1, sizeof memo);
  long long sol = 0;
  for (int x : v)
    sol += dp(256, x);

  printf("%lld\n", sol);

  return 0;
}
