#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

const map<char, char> MATCH = {
  {'(', ')'},
  {'[', ']'},
  {'{', '}'},
  {'<', '>'}
};

const map<char, int> ERROR = {
  {')', 3},
  {']', 57},
  {'}', 1197},
  {'>', 25137}
};

int parse(const string &line) {
  stack<char> s;
  for (auto c : line)
    if (MATCH.count(c))
      s.push(c);
    else {
      assert(!s.empty());
      char top = s.top();
      s.pop();
      if (MATCH.at(top) != c)
        return ERROR.at(c);
    }
  return 0;
}

int main() {
  int total = 0;
  string line;
  while (cin >> line)
    total += parse(line);
  cout << total << endl;
  return 0;
}
