#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <class T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

#define TRACE(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#define _ << " _ " <<

template <class T, class U> ostream &operator<<(ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}
template <class> struct is_container : false_type {};
template <class... Ts> struct is_container<vector<Ts...>> : true_type {};
template <class... Ts> struct is_container<map<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template <class... Ts> struct is_container<set<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template <class... Ts> struct is_container<multiset<Ts...>> : true_type {};
template <class... Ts>
struct is_container<unordered_multiset<Ts...>> : true_type {};
template <class T, class = typename enable_if<is_container<T>::value>::type>
ostream &operator<<(ostream &o, T x) {
  int f = 1;
  o << "{";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "}";
}

typedef long long llint;

const int MAXN = 200;

const int dr[] = {1, 0, -1, 0};
const int ds[] = {0, 1, 0, -1};

bool bio[MAXN][MAXN];

char grid[MAXN][MAXN];

int r, s;

inline bool inside(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s;
}

pair<int, int> dfs(int rr, int ss) {
  int area = 1, sides = 0;
  bio[rr][ss] = true;

  for (int i = 0; i < 4; ++i) {
    int nr = rr + dr[i], ns = ss + ds[i];
    int mr = rr + dr[(i + 1) % 4], ms = ss + ds[(i + 1) % 4];

    bool sn = !inside(nr, ns) || grid[rr][ss] != grid[nr][ns];
    bool sm = !inside(mr, ms) || grid[rr][ss] != grid[mr][ms];
    sides += sn & sm;

    if (!sn && !sm && inside(mr + dr[i], ms + ds[i]) &&
        grid[mr + dr[i]][ms + ds[i]] != grid[rr][ss])
      ++sides;

    if (!inside(nr, ns) || grid[nr][ns] != grid[rr][ss] || bio[nr][ns])
      continue;
    const auto &p = dfs(nr, ns);
    area += p.first;
    sides += p.second;
  }

  return {area, sides};
}

int main(void) {
  while (scanf("%s", grid[r]) == 1)
    r++;
  s = strlen(grid[0]);

  int sol = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (bio[i][j])
        continue;
      const auto &p = dfs(i, j);
      sol += p.first * p.second;
    }
  }

  printf("%d\n", sol);

  return 0;
}
