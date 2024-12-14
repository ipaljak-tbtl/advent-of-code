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

const int MAXN = 5e2 + 10;

const int X = 101;
const int Y = 103;

int n, q1, q2, q3, q4;
int x[MAXN], y[MAXN], dx[MAXN], dy[MAXN];

inline int add(int a, int b, int mod) {
  if (a + b >= mod)
    return a + b - mod;
  if (a + b < 0)
    return a + b + mod;
  return a + b;
}

inline int mul(int a, int b, int mod) { return (llint)a * b % mod; }

int main(void) {
  while (scanf("p=%d,%d v=%d,%d\n", &x[n], &y[n], &dx[n], &dy[n]) == 4) {
    x[n] = add(x[n], mul(100, dx[n], X), X);
    y[n] = add(y[n], mul(100, dy[n], Y), Y);

    TRACE(x[n] _ y[n]);

    q1 += x[n] < X / 2 && y[n] < Y / 2;
    q2 += x[n] < X / 2 && y[n] > Y / 2;
    q3 += x[n] > X / 2 && y[n] < Y / 2;
    q4 += x[n] > X / 2 && y[n] > Y / 2;

    ++n;
  }

  TRACE(q1 _ q2 _ q3 _ q4);
  printf("%d\n", q1 * q2 * q3 * q4);

  return 0;
}
