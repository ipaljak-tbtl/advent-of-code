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

map<string, set<string>> m;

int main(void) {
  string line;
  while (cin >> line) {
    m[line.substr(0, 2)].insert(line.substr(3, 2));
    m[line.substr(3, 2)].insert(line.substr(0, 2));
  }

  set<set<string>> clique3;

  for (const auto &p : m) {
    string a = p.first;
    for (const auto &b : p.second)
      for (const auto &c : p.second)
        if (m[b].find(c) != m[b].end())
          clique3.insert({a, b, c});
  }

  TRACE(clique3.size());
  TRACE(clique3);

  int sol = 0;
  for (const auto &clq : clique3) {
    bool ok = false;
    for (const auto &node : clq)
      ok |= node[0] == 't';
    sol += ok;
  }

  printf("%d\n", sol);
  return 0;
}
