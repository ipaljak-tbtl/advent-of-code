#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

map<char, int> autocomplete_score;
map<char, char> match;

inline void init() {
  match['('] = ')';
  match['['] = ']';
  match['{'] = '}';
  match['<'] = '>';
  autocomplete_score[')'] = 1;
  autocomplete_score[']'] = 2;
  autocomplete_score['}'] = 3;
  autocomplete_score['>'] = 4;
}

llint get_score(const string &line) {
  stack<char> st;
  for (char c : line) {
    if (autocomplete_score.find(c) == autocomplete_score.end()) {
      st.push(c);
      continue;
    }
    if (st.empty() || abs(c - st.top()) > 2) return -1;
    st.pop();
  }

  llint ret = 0;
  while (!st.empty()) {
    ret *= 5LL;
    ret += (llint)autocomplete_score[match[st.top()]];
    st.pop();
  }

  return ret;
}

int main(void) {
  init();

  string line;
  vector<llint> scores;

  while (cin >> line) {
    llint score = get_score(line);
    if (score != -1) scores.push_back(score);
  }

  sort(scores.begin(), scores.end());
  cout << scores[scores.size() / 2] << endl;

  return 0;
}
