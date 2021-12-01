#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  int l1 = -1;
  int l2 = -1;
  int l3 = -1;
  int current = -1;
  int count = 0;
  while (cin >> current) {
    if (l3 != -1 && current > l3)
      count++;
    l3 = l2;
    l2 = l1;
    l1 = current;
  }
  cout << count << endl;
  return 0;
}
