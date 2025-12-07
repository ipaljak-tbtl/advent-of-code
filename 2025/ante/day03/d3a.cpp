#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


int main() {
  int sum = 0;
  string line;
  while (cin >> line) {
    assert(line.find('0') == string::npos);
    auto first = max_element(line.begin(), --line.end());
    auto second = max_element(first + 1, line.end());
    int curr = (*first - '0') * 10 + (*second - '0');
    TRACE(curr);
    sum += curr;
  }
  cout << sum << endl;
  return 0;
}
