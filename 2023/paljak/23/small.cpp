#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

const map<char, pair<int, int>> DIR = {
  {'>', {0, 1}},
  {'v', {1, 0}},
  {'<', {0, -1}},
  {'^', {-1, 0}}
};

set<pair<int, int>> visited;

int n, sol;
char grid[MAXN][MAXN];

inline bool check(int r, int s) {
  return r >= 0 && r < n && s >= 0 && s < n && grid[r][s] != '#' && visited.find({r, s}) == visited.end();
}

void dfs(int r, int s, int d) {
  if (r == n - 1 && s == n - 2) {
    sol = max(sol, d);
    return;
  }
  
  for (auto &p : DIR) {
    if (grid[r][s] != '.' && grid[r][s] != p.first) continue;
    int rr = r + p.second.first, ss = s + p.second.second;
    if (!check(rr, ss)) continue;
    visited.insert({rr, ss});
    dfs(rr, ss, d + 1);
    visited.erase({rr, ss});
  }
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1);
  --n;

  visited.insert({0, 1});
  dfs(0, 1, 0);

  printf("%d\n", sol);

  return 0;
} 
