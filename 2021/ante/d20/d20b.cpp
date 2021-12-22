#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

string rules;
int invert = 0;
set<pair<int, int>> on;

void step() {
  auto [lox, loy] = *on.begin();
  auto [hix, hiy] = *on.begin();
  for (auto [x, y] : on) {
    lox = min(lox, x);
    hix = max(hix, x);
    loy = min(loy, y);
    hiy = max(hiy, y);
  }
  set<pair<int, int>> off;
  for (int x = lox-1; x <= hix+1; x++)
    for (int y = loy-1; y <= hiy+1; y++) {
      int mask = 0;
      for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
          mask = (mask << 1) | on.count({x+dx, y+dy});
      if (invert) {
        mask ^= (1<<9)-1;
        if (rules[mask] == '#')
          off.insert({x, y});
      } else {
        if (rules[mask] == '.')
          off.insert({x, y});
      }
    }
  
  swap(on, off);
  invert = 1-invert;       
}

int main() {
  cin >> rules;
  string line;
  int i = 0;
  while (cin >> line) {
    for (int j=0; j<(int)line.size(); j++)
      if (line[j] == '#')
        on.insert({i, j});
    i++;
  }
  for (int i=0; i<50; i++)
    step();
  cout << on.size() << endl;
  return 0;
}
