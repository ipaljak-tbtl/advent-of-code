#include <bits/stdc++.h>

using namespace std;

string s;

int main(void) {
  cin >> s;
  for (int i = 13; i < (int) s.size(); ++i) {
    set<char> st;
    for (int j = 0; j < 14; ++j)
      st.insert(s[i - j]);
    if (st.size() == 14) {
      cout << i + 1 << endl;
      return 0;
    }
  }

  assert(false);
  return 0;
}
