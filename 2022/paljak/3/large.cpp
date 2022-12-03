#include <bits/stdc++.h>

using namespace std;

int priority(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a' + 1;
  return c - 'A' + 27;
}

char common(const string &s1, const string &s2, const string &s3) {
  set<char> ss1(s1.begin(), s1.end()), ss2(s2.begin(), s2.end()),
      ss3(s3.begin(), s3.end());
  for (char c = 'a'; c <= 'z'; ++c)
    if (ss1.find(c) != ss1.end() && ss2.find(c) != ss2.end() &&
        ss3.find(c) != ss3.end())
      return c;
  for (char c = 'A'; c <= 'Z'; ++c)
    if (ss1.find(c) != ss1.end() && ss2.find(c) != ss2.end() &&
        ss3.find(c) != ss3.end())
      return c;
  assert(false);
}

int main(void) {
  string s1, s2, s3;
  int sol = 0;
  while (cin >> s1 >> s2 >> s3) {
    sol += priority(common(s1, s2, s3));
  }
  cout << sol << endl;
  return 0;
}
