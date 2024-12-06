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

const int MAXN = 150;

const int dr[] = {-1, 0, 1, 0};
const int ds[] = {0, 1, 0, -1};

int r, s;
char grid[MAXN][MAXN];

set<int> visited[MAXN][MAXN];

inline bool inside(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s;
}

inline void clear_grid() {
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      visited[i][j].clear();
}

int move(int gr, int gs, int dir) {
  if (visited[gr][gs].find(dir) != visited[gr][gs].end())
    return 1;
  visited[gr][gs].insert(dir);

  int rr = gr + dr[dir], ss = gs + ds[dir];
  if (!inside(rr, ss))
    return 0;

  if (grid[rr][ss] == '#')
    return move(gr, gs, (dir + 1) % 4);
  else
    return move(rr, ss, dir);
}

int main(void) {
  while (scanf("%s", grid[r]) == 1)
    ++r;
  s = strlen(grid[0]);

  int gr, gs;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] == '^')
        gr = i, gs = j;

  int sol = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if ((i == gr && i == gs) || grid[i][j] == '#')
        continue;
      clear_grid();
      grid[i][j] = '#';
      sol += move(gr, gs, 0);
      grid[i][j] = '.';
    }
  }

  printf("%d\n", sol);

  return 0;
}
