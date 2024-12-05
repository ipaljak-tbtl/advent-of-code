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

set<pair<int, int>> edges;

int eval(const vector<int> &v) {
  for (int i = 0; i < (int)v.size(); ++i)
    for (int j = i + 1; j < (int)v.size(); ++j)
      if (edges.count({v[j], v[i]}) != 0)
        return 0;
  return v[(int)v.size() / 2];
}

int main(void) {
  int a, b;
  while (scanf("%d|%d", &a, &b) == 2)
    edges.insert({a, b});

  vector<int> v;
  char line[1024];
  int sol = 0;

  while (scanf("%s", line) == 1) {
    v.clear();
    int curr = 0;
    for (int i = 0; i < strlen(line); ++i) {
      char c = line[i];
      if (c == ',') {
        v.push_back(a);
        a = 0;
        continue;
      }
      a = a * 10 + c - '0';
    }
    v.push_back(a);
    a = 0;
    sol += eval(v);
  }

  printf("%d\n", sol);
  return 0;
}
