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

const int MAXN = 55;

int r, s;
char grid[MAXN][MAXN];

inline bool inside(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s;
}

int main(void) {
  while (scanf("%s", grid[r]) == 1)
    ++r;

  s = strlen(grid[0]);

  map<int, vector<pair<int, int>>> m;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] != '.')
        m[grid[i][j]].emplace_back(i, j);

  set<pair<int, int>> sol;
  for (const auto &entry : m) {
    for (const auto &p1 : entry.second) {
      for (const auto &p2 : entry.second) {
        if (p1 == p2)
          continue;
        int rr = p1.first + (p1.first - p2.first);
        int ss = p1.second + (p1.second - p2.second);
        sol.insert({p1.first, p1.second});
        while (inside(rr, ss)) {
          sol.insert({rr, ss});
          rr += (p1.first - p2.first);
          ss += (p1.second - p2.second);
        }
      }
    }
  }

  printf("%d\n", (int)sol.size());

  return 0;
}
