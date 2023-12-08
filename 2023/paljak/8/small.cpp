#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int n;
char moves[MAXN];

map<string, pair<string, string>> nodes;

int main(void) {
  scanf("%s", moves);
  n = strlen(moves);

  char a[10], b[10], c[10];
  while (scanf("%s %s %s", a, b, c) == 3)
    nodes[string(a)] = {string(b), string(c)};

  string s = "AAA";
  string t = "ZZZ";

  int i = 0, sol = 0;
  while (s != t) {
    if (moves[i] == 'L')
      s = nodes[s].first;
    else
      s = nodes[s].second;
    ++sol;
    i = (i + 1) % n;
  }

  printf("%d\n", sol);

  return 0;
}
