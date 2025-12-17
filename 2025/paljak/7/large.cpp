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

int r, s;
char grid[MAXN][MAXN];
llint dp[MAXN][MAXN];

int main(void) {
  while (scanf("%s", grid[r++]) != EOF)
    ;
  s = strlen(grid[0]);

  for (int i = 0; i < s; ++i)
    if (grid[0][i] == 'S')
      dp[0][i] = 1LL;

  for (int i = 1; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (grid[i][j] == '^')
        continue;
      dp[i][j] = dp[i - 1][j];
      if (j - 1 >= 0 && grid[i][j - 1] == '^')
        dp[i][j] += dp[i - 1][j - 1];
      if (j + 1 < s && grid[i][j + 1] == '^')
        dp[i][j] += dp[i - 1][j + 1];
    }
  }

  llint sol = 0;
  for (int i = 0; i < s; ++i)
    sol += dp[r - 1][i];

  printf("%lld\n", sol);

  return 0;
}
