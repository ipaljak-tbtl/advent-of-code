#include <bits/stdc++.h>

using namespace std;

int f(const string &s) {
  auto lo = find_if(s.begin(), s.end(), ::isdigit);
  auto hi = find_if(s.rbegin(), s.rend(), ::isdigit);
  return (*lo - '0') * 10 + (*hi - '0');
}

int main(void) {
  string s;
  int sol = 0;

  while (cin >> s)
    sol += f(s);

  printf("%d\n", sol);
  return 0;
}
