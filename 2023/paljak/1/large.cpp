#include <bits/stdc++.h>

using namespace std;

const vector<string> digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

vector<pair<int, int>> find_matches(const string &s) {
  vector<pair<int, int>> matches;
  for (int i = 0; i < (int)s.length(); ++i) {
    if (isdigit(s[i])) matches.emplace_back(i, s[i] - '0');
    for (int j = 0; j < (int)digits.size(); ++j)
      if (s.rfind(digits[j], i) == i)
        matches.emplace_back(i, j + 1);
  }
  return matches;
}

int f(const string &s) {
  auto matches = find_matches(s);
  int lo = min_element(matches.begin(), matches.end())->second;
  int hi = max_element(matches.begin(), matches.end())->second;
  return lo * 10 + hi;
}

int main(void) {
  string s;
  int sol = 0;

  while (cin >> s)
    sol += f(s);

  printf("%d\n", sol);
  return 0;
}
