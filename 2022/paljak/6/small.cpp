#include <bits/stdc++.h>

using namespace std;

string s;

int main(void) {
  cin >> s;
  for (int i = 3; i < (int) s.size(); ++i) {
    set<char> st;
    for (int j = 0; j < 4; ++j)
      st.insert(s[i - j]);
    if (st.size() == 4) {
      cout << i + 1 << endl;
      return 0;
    }
  }

  assert(false);
  return 0;
}
