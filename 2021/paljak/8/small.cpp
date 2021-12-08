#include <bits/stdc++.h>

using namespace std;

int main(void) {
  int sol = 0;
  string s;
  while (cin >> s) {
    while (s != "|") cin >> s;
    for (int i = 0; i < 4; ++i) {
      cin >> s;
      sol += s.size() == 2 || s.size() == 4 || s.size() == 3 || s.size() == 7;
    }
  }

  cout << sol << endl;
  return 0;
}
