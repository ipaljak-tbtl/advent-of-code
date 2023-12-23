#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

set<pair<int, int>> visited;
map<pair<int, int>, vector<pair<int, int>>> G;

int n, sol;
char grid[MAXN][MAXN];

inline bool check(int r, int s) {
  return r >= 0 && r < n && s >= 0 && s < n && grid[r][s] != '#';
}

void dfs(int r, int s, int d) {
  if (r == n - 1 && s == n - 2) {
    if (d > sol)
      printf("%d\n", d);
    sol = max(sol, d);
    return;
  }
  
  for (auto nxt : G[{r, s}]) {
    if (visited.find(nxt) != visited.end()) continue;
    visited.insert(nxt);
    dfs(nxt.first, nxt.second, d + abs(nxt.first - r) + abs(nxt.second - s));
    visited.erase(nxt);
  }
}

void build_graph() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == '#') continue;
      for (int k = 0; k < 4; ++k) {
        int ii = i + dr[k], jj = j + ds[k];
        if (!check(ii, jj)) continue;
        G[{i, j}].emplace_back(ii, jj);
      }
    }
  }
}

void contract_edges() {
  pair<int, int> to_remove;
  do {
    to_remove = {-1, -1};
    for (auto p : G) {
      if (p.second.size() != 2) continue;
      if (p.second[0].first != p.second[1].first && p.second[0].second != p.second[1].second) continue;
      auto l = p.second[0], r = p.second[1];
      G[l].erase(find(G[l].begin(), G[l].end(), p.first));
      G[l].push_back(r);
      G[r].erase(find(G[r].begin(), G[r].end(), p.first));
      G[r].push_back(l);
      to_remove = p.first;
      break;
    }
    G.erase(to_remove);
  } while (to_remove !=  make_pair(-1, -1));
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1);
  --n;


  build_graph();
  contract_edges();

  visited.insert({0, 1});
  dfs(0, 1, 0);

  printf("%d\n", sol);

  return 0;
} 
