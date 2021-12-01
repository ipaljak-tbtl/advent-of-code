#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  int last = -1;
  int current = -1;
  int count = 0;
  while (cin >> current) {
    if (last != -1 && current > last)
      count++;
    last = current;
  }
  cout << count << endl;
  return 0;
}
