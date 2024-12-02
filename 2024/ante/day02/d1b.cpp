#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


int is_safe(const vector<int> levels) {
  int increasing = -1;
  int last = -1;
  for (auto const current : levels) { 
    if (last == -1) {
      last = current;
      continue ;
    }
    if (last == current || abs(current-last) > 3)
      return 0;
    if (increasing == -1) {
      increasing = last < current;
      last = current;
      continue ;
    }
    if (increasing != (last < current))
      return 0;
    last = current;
  }
  return 1;
}


int main() {
  string line;
  int safe = 0;
  
  while (getline(cin, line)) {
    istringstream in(line);
    vector<int> a;
    int x;
    while (in >> x)
      a.push_back(x);
    
    if (is_safe(a)) {
      safe++;
      continue ;
    }

    for (int i=0; i<(int)a.size(); i++) {
      vector<int> b = a;
      b.erase(b.begin()+i);
      if (is_safe(b)) {
        safe++;
        break ;
      }
    }
  }
  
  cout << safe << endl;
  return 0;
}
