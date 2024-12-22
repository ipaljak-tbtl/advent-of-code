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

struct Rng {
  static const llint MOD = 16777216LL;
  llint seed;

  Rng() {}
  Rng(int seed) : seed(seed) {}

  llint next() {
    seed = prune(mix(seed, seed * 64LL));
    seed = prune(mix(seed, seed / 32LL));
    seed = prune(mix(seed, seed * 2048LL));
    return seed;
  }

  static llint prune(llint x) { return x % MOD; }

  static llint mix(llint x, llint y) { return x ^ y; }
};

int main(void) {
  llint sol = 0, seed;
  while (scanf("%lld", &seed) == 1) {
    Rng rng(seed);
    llint num;
    for (int i = 0; i < 2000; ++i)
      num = rng.next();
    TRACE(num);
    sol += num;
  }

  printf("%lld\n", sol);

  return 0;
}
