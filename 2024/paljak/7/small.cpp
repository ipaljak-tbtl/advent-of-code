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

bool check(const vector<llint> &v, llint target) {
  for (int mask = 0; mask < 1 << ((int)v.size() - 1); ++mask) {
    llint curr = v[0];
    for (int i = 1; i < (int)v.size(); ++i) {
      if ((mask & (1 << (i - 1))))
        curr += v[i];
      else
        curr *= v[i];
    }
    if (curr == target)
      return true;
  }
  return false;
}

int main(void) {
  llint target, sol = 0;
  while (scanf("%lld:", &target) == 1) {
    char c;
    llint x;
    vector<llint> v;
    while (scanf("%lld%c", &x, &c) == 2) {
      v.push_back(x);
      if (c == '\n')
        break;
    }
    if (check(v, target))
      sol += (llint)target;
  }

  printf("%lld\n", sol);
  return 0;
}
