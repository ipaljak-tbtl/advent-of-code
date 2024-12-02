#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


int main() {
  string line;
  int safe = 0;
  
  while (getline(cin, line)) {
    istringstream in(line);
    int increasing = -1;
    int last = -1;
    int current;
    int is_safe = 1;

    while (in >> current) {
      if (last == -1) {
        last = current;
        continue ;
      }
      if (last == current || abs(current-last) > 3) {
        is_safe = 0;
        break ;
      }
      if (increasing == -1) {
        increasing = last < current;
        last = current;
        continue ;
      }
      if (increasing != (last < current)) {
        is_safe = 0;
        break ;
      }
      last = current;
    }
    safe += is_safe;

  }
  
  cout << safe << endl;
  return 0;
}
