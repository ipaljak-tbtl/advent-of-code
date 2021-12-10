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

const map<char, int> SCORE = {
  {'(', 1},
  {'[', 2},
  {'{', 3},
  {'<', 4}
};

long long parse(const string &line) {
  stack<char> s;
  for (auto c : line)
    if (MATCH.count(c))
      s.push(c);
    else {
      assert(!s.empty());
      char top = s.top();
      s.pop();
      if (MATCH.at(top) != c)
        return -1;
    }
  long long score = 0;
  while (!s.empty()) {
    char top = s.top();
    s.pop();
    score = score*5+SCORE.at(top);
  }
  return score;
}

int main() {
  vector<long long> scores;
  string line;
  while (cin >> line) {
    long long s = parse(line);
    if (s > 0)
      scores.push_back(s);
  }
  sort(scores.begin(), scores.end());
  cout << scores[(int)scores.size()/2] << endl;
  return 0;
}
