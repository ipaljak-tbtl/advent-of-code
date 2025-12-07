#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


int main() {
  llint sum = 0;
  string line;
  while (cin >> line) {
    assert(line.find('0') == string::npos);
    llint curr = 0;
    auto start = line.begin();
    for (int i=0; i<12; i++) {
      auto next = max_element(start, line.end()-12+1+i);
      curr = curr * 10 + (*next - '0');
      start = next + 1;
    }
    TRACE(curr);
    sum += curr;
  }
  cout << sum << endl;
  return 0;
}
