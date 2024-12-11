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

map<pair<llint, int>, llint> memo;

llint dp(llint num, int n) {
  if (memo.find({num, n}) != memo.end())
    return memo[{num, n}];

  if (n == 0)
    return memo[{num, n}] = 1LL;

  if (num == 0)
    return memo[{num, n}] = dp(1, n - 1);

  string x_str = to_string(num);
  if (x_str.size() % 2 == 1)
    return memo[{num, n}] = dp(2024LL * num, n - 1);

  if (num == 0)
    return memo[{num, n}] = dp(1, n - 1);

  auto l = x_str.substr(0, x_str.size() / 2);
  auto r = x_str.substr(x_str.size() / 2, x_str.size() / 2);

  llint ret = dp(stoll(l, nullptr, 10), n - 1);
  ret += dp(stoll(r, nullptr, 10), n - 1);

  return memo[{num, n}] = ret;
}

int main(void) {
  int x;
  llint sol = 0;
  while (scanf("%d", &x) == 1)
    sol += dp((llint)x, 75);

  printf("%lld\n", sol);

  return 0;
}
