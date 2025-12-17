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

int n;
vector<pair<int, int>> p;

inline bool check(int i, int j) {
  for (int k = 0; k < n; ++k) {
    int l = (k + 1) % n;
    int lo_x =
        max(min(p[k].first, p[l].first), min(p[i].first + 1, p[j].first + 1));
    int lo_y = max(min(p[k].second, p[l].second),
                   min(p[i].second + 1, p[j].second + 1));
    int hi_x =
        min(max(p[k].first, p[l].first), max(p[i].first - 1, p[j].first - 1));
    int hi_y = min(max(p[k].second, p[l].second),
                   max(p[i].second - 1, p[j].second - 1));
    if (lo_x <= hi_x && lo_y <= hi_y)
      return false;
  }
  return true;
}

int main(void) {
  int r, s;
  while (scanf("%d,%d", &r, &s) != EOF)
    p.emplace_back(r, s);

  n = (int)p.size();

  llint sol = 0;
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
      if (!check(i, j))
        continue;
      sol = max(sol, (llint)(abs(p[i].first - p[j].first) + 1) *
                         (abs(p[i].second - p[j].second) + 1));
    }

  printf("%lld\n", sol);

  return 0;
}
