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

const int MAXN = 2e4 + 10;

char s[MAXN];

int n;
int deflated[5 * MAXN];

int main(void) {
  scanf("%s", s);
  n = strlen(s);

  int m = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < (int)(s[i] - '0'); ++j)
      if (i % 2 == 0)
        deflated[m++] = i / 2;
      else
        deflated[m++] = -1;
  }

  int hi = m - 1;
  while (hi >= 0) {
    if (deflated[hi] == -1) {
      --hi;
      continue;
    }

    int sz = 1;
    while (hi - 1 >= 0 && deflated[hi - 1] == deflated[hi]) {
      --hi;
      ++sz;
    }

    for (int i = 0; i + sz <= hi; ++i) {
      bool empty = deflated[i] == -1;
      for (int j = i + 1; j < i + sz && empty; ++j)
        empty &= deflated[j] == -1;
      if (!empty)
        continue;
      for (int j = 0; j < sz; ++j)
        swap(deflated[i + j], deflated[hi + j]);
      break;
    }

    --hi;
  }

  llint sol = 0;
  for (int i = 0; i < m; ++i) {
    if (deflated[i] == -1)
      continue;
    sol += (llint)i * deflated[i];
  }

  printf("%lld\n", sol);

  return 0;
}
