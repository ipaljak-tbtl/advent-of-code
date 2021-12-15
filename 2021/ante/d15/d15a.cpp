#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef pair<int, pair<int, int>> qelem;

int n;
int m;
vector<string> G;

int dijkstra() {
  priority_queue<qelem, vector<qelem>, greater<qelem>> Q;
  vector<vector<int>> D(n, vector<int>(m, 0));

  Q.push({0, {0, 0}});
  while (!Q.empty()) {
    auto [c, p] = Q.top();
    auto [x, y] = p;
    Q.pop();
    if (D[x][y])
      continue ;
    D[x][y] = 1;
    if (x == n-1 && y == m-1)
      return c;
    for (auto [xx, yy] : vector<pair<int, int>>{{x-1, y}, {x+1, y}, {x, y-1}, {x, y+1}}) {
      if (xx < 0 || xx > n-1 || yy < 0 || yy > m-1)
        continue ;
      if (D[xx][yy])
        continue ;
      Q.push({c+G[xx][yy]-'0', {xx, yy}});
    }
  }
  
  assert(false);
}

int main() {
  string s;
  while (cin >> s)
    G.push_back(s);
  n = G.size();
  m = G[0].size();

  cout << dijkstra() << endl;
  
  return 0;
}
