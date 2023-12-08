#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

typedef long long llint;

int n;
char moves[MAXN];

map<string, pair<string, string>> nodes;

int dist(string s) {
  int i = 0, sol = 0;
  while (s[2] != 'Z') {
    if (moves[i] == 'L')
      s = nodes[s].first;
    else
      s = nodes[s].second;
    ++sol;
    i = (i + 1) % n;
  }
  return sol;
}

llint lcm(llint a, llint b) {
  // pray
  return a * b / __gcd(a, b);
}

int main(void) {
  scanf("%s", moves);
  n = strlen(moves);

  char a[10], b[10], c[10];
  while (scanf("%s %s %s", a, b, c) == 3)
    nodes[string(a)] = {string(b), string(c)};

  llint sol = 1;
  for (auto &p : nodes) {
    if (p.first[2] != 'A') continue;
    sol = lcm(sol, dist(p.first));
  }

  printf("%lld\n", sol);

  return 0;
}
