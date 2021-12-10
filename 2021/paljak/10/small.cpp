#include <bits/stdc++.h>

using namespace std;

map<char, int> error_score;

inline void init() {
  error_score[')'] = 3;
  error_score[']'] = 57;
  error_score['}'] = 1197;
  error_score['>'] = 25137;
}

int get_score(const string &line) {
  stack<char> st;
  for (char c : line) {
    if (error_score.find(c) == error_score.end()) {
      st.push(c);
      continue;
    }
    if (st.empty() || abs(c - st.top()) > 2) return error_score[c];
    st.pop();
  }
  return 0;
}

int main(void) {
  init();

  int sol = 0;
  string line;

  while (cin >> line) sol += get_score(line);

  cout << sol << endl;
  return 0;
}
