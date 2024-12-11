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

multiset<llint> s[2];

void blink(int curr, int prev) {
  TRACE(s[curr].size());
  s[prev].clear();
  for (llint x : s[curr]) {
    if (x == 0) {
      s[prev].insert(1);
      continue;
    }

    string x_str = to_string(x);
    if (x_str.size() % 2 == 1) {
      s[prev].insert(2024LL * x);
      continue;
    }

    auto l = x_str.substr(0, x_str.size() / 2);
    auto r = x_str.substr(x_str.size() / 2, x_str.size() / 2);

    s[prev].insert(stoll(l, nullptr, 10));
    s[prev].insert(stoll(r, nullptr, 10));
  }
}

int main(void) {
  int x, curr = 0, prev = 1;
  while (scanf("%d", &x) == 1)
    s[curr].insert(x);

  for (int i = 0; i < 25; ++i) {
    blink(curr, prev);
    swap(curr, prev);
  }

  printf("%d\n", (int)s[curr].size());

  return 0;
}
