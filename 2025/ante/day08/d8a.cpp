#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


int n;
vector<int> x;
vector<int> y;
vector<int> z;
vector<vector<int>> g;
const int T = 1000;
vector<int> bio;


int dfs(int v) {
  bio[v] = 1;
  int sz = 1;
  for (int u=0; u<n; u++) {
    if (g[v][u] && !bio[u]) {
      sz += dfs(u);
    }
  }
  return sz;
}


int main() {
  llint a, b, c;
  while (scanf("%lld,%lld,%lld", &a, &b, &c) == 3) {
    x.push_back(a);
    y.push_back(b);
    z.push_back(c);
  }

  n = x.size();
  g = vector<vector<int>>(n, vector<int>(n, 0));
  
  vector<pair<llint, pair<int, int>>> dist;
  for (int i = 0; i < n; i++) 
    for (int j = i+1; j < n; j++) {
      llint dx = x[i] - x[j];
      llint dy = y[i] - y[j];
      llint dz = z[i] - z[j];
      llint d = dx*dx + dy*dy + dz*dz;
      dist.push_back({d, {i, j}});
    }
  sort(dist.begin(), dist.end());
  
  for (int i=0; i<T; i++) {
    g[dist[i].second.first][dist[i].second.second] = 1;
    g[dist[i].second.second][dist[i].second.first] = 1;
  }

  bio = vector<int>(n, 0);
  vector<int> sizes;
  for (int i=0; i<n; i++)
    if (!bio[i])
      sizes.push_back(dfs(i));
  sort(sizes.begin(), sizes.end(), greater<int>());

  int total = sizes[0]*sizes[1]*sizes[2];
  cout << total << endl;

  return 0;
}
