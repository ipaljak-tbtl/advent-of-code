#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  int n = 0;
  int len = 0;
  vector<int> freq;
  string line;
  while (cin >> line) {
    n++;
    if (len == 0) {
      len = line.size();
      freq = vector<int>(len);
    }
    assert((int)line.size() == len);
    for (int i=0; i<len; i++)
      if (line[i] == '1')
        freq[i]++;
  }
  int cx = 0;
  int cy = 0;
  for (int i=0; i<len; i++) {
    cx <<= 1;
    cy <<= 1;
    if (2*freq[i] >= n)
      cx |= 1;
    else
      cy |= 1;
  }
  cout << cx*cy << endl;
  return 0;
}
