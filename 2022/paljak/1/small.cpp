#include <bits/stdc++.h>

using namespace std;

int main(void) {
  int curr = 0, best = 0;

  while (cin.peek() != EOF) {
    string line;
    getline(cin, line);
    if (line.empty()) {
      best = max(best, curr);
      curr = 0;
      continue;
    }
    curr += stoi(line);
  }

  cout << max(best, curr) << endl;

  return 0;
}
