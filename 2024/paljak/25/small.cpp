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

vector<vector<int>> lck, key;

char schema[10][10];

void parse_schema() {
  vector<int> hist;
  for (int j = 0; j < 5; ++j) {
    int cnt = 0;
    for (int i = 1; i < 7 && schema[i][j] == schema[i - 1][j]; ++i)
      ++cnt;
    hist.push_back(cnt);
  }

  if (schema[0][0] == '#')
    lck.push_back(hist);
  else
    key.push_back(hist);
}

bool fit(const vector<int> &l, const vector<int> &k) {
  bool ret = true;
  for (int i = 0; i < 5; ++i)
    ret &= (l[i] + 5 - k[i]) < 6;
  return ret;
}

int main(void) {
  while (scanf("%s", schema[0]) == 1) {
    for (int i = 1; i < 7; ++i)
      scanf("%s", schema[i]);

    parse_schema();
  }

  int sol = 0;
  for (const auto &l : lck)
    for (const auto &k : key)
      sol += fit(l, k);

  printf("%d\n", sol);
  return 0;
}
