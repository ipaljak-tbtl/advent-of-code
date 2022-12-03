#include <bits/stdc++.h>

using namespace std;

int priority(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a' + 1;
  return c - 'A' + 27;
}

char common(const string &s) {
  set<char> ss;
  for (int i = 0; i < (int)s.size() / 2; ++i)
    ss.insert(s[i]);
  for (int i = (int) s.size() / 2; i < (int) s.size(); ++i)
    if (ss.find(s[i]) != ss.end())
      return s[i];
  assert(false);
}

int main(void) {
  string s;
  int sol = 0;
  while (cin >> s)
    sol += priority(common(s));
  cout << sol << endl;
  return 0;
}
