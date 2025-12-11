#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

int goal;
vector<int> switches;

int solve() {
  queue<pair<int, int>> Q;
  set<int> done;
  Q.push({0, 0});
  while (!Q.empty()) {
    auto [state, dist] = Q.front(); 
    Q.pop();
    if (state == goal) 
      return dist;
    for (int sw : switches) {
      int nstate = state ^ sw;
      if (done.count(nstate)) 
        continue;
      done.insert(nstate);
      Q.push({nstate, dist+1});
    }
  } 
  return -1;
}

int main() {
  int total = 0;
  string item;
  while (cin >> item) {
    string inside = item.substr(1, item.size()-2);
    if (item[0] == '[') {
      goal = 0;
      for (int i=0; i<(int)inside.size(); i++)
        if (inside[i] == '#') 
          goal |= (1 << i);
      switches.clear();
    } else if (item[0] == '(') {
      int x = 0;
      for (const auto word : std::views::split(inside, ','))
        x |= (1 << stoi(string(string_view(word))));
      switches.push_back(x);
    } else if (item[0] == '{') {
      int res = solve();
      assert(res >= 0);
      TRACE(res);
      total += res;
    }
  }
  cout << total << endl;
  return 0;
}
