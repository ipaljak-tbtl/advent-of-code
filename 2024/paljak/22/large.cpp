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

const int MAXN = 2300;

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

map<vector<int>, int> m[MAXN];
vector<vector<int>> all_patterns;

void gen_all(vector<int> curr) {
  if (curr.size() == 4) {
    all_patterns.push_back(curr);
    return;
  }

  for (int i = -9; i < 10; ++i) {
    curr.push_back(i);
    gen_all(curr);
    curr.pop_back();
  }
}

int main(void) {
  int id = 0;
  llint seed;
  while (scanf("%lld", &seed) == 1) {
    TRACE(id);
    vector<int> delta, prices;
    Rng rng(seed);
    int prev = (int)(seed % 10);
    for (int i = 0; i < 2000; ++i) {
      int curr = (int)(rng.next() % 10);
      delta.emplace_back(curr - prev);
      prices.emplace_back(curr);
      prev = curr;
    }

    for (int i = 0; i < (int)delta.size() - 4; ++i) {
      vector<int> pattern;
      for (int j = i; j < i + 4; ++j)
        pattern.push_back(delta[j]);
      if (m[id].find(pattern) == m[id].end())
        m[id][pattern] = prices[i + 4 - 1];
    }
    id++;
  }

  int sol = 0;
  gen_all({});
  for (const auto &pattern : all_patterns) {
    int curr = 0;
    for (int i = 0; i < id; ++i) {
      auto entry = m[i].find(pattern);
      if (entry != m[i].end())
        curr += entry->second;
    }
    if (curr > sol)
      TRACE(pattern);
    sol = max(sol, curr);
  }

  printf("%d\n", sol);

  return 0;
}
