#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int read_input(vector<string> &digits, vector<string> &query) {
  digits.resize(10);
  query.resize(4);
  for (int i=0; i<10; i++)
    if (!(cin >> digits[i]))
        return 0;        
  string s;
  cin >> s;
  assert(s == "|");
  for (int i=0; i<4; i++)
    if (!(cin >> query[i]))
      return 0;
  return 1;
}

int main() {
  vector<string> digits;
  vector<string> query;
  
  int total = 0;
  while (read_input(digits, query)) {
    for (auto &s : query)
      if (s.size() == 2 || s.size() == 4 || s.size() == 3 || s.size() == 7)
        total++;
  }
  
  cout << total << endl;
  return 0;
}
