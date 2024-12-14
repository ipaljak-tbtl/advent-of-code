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

void print() {
  char canvas[X + 1][Y + 1];
  memset(canvas, '.', sizeof canvas);

  for (int i = 0; i < n; ++i)
    canvas[x[i]][y[i]] = '*';

  for (int i = 0; i < X; ++i) {
    for (int j = 0; j < Y; ++j)
      printf("%c", canvas[i][j]);
    printf("\n");
  }
  printf("\n\n");
}

int main(void) {
  while (scanf("p=%d,%d v=%d,%d\n", &x[n], &y[n], &dx[n], &dy[n]) == 4)
    ++n;

  int best = 1e9;
  for (int t = 0; t < 10000; ++t) {
    for (int i = 0; i < n; ++i) {
      x[i] = add(x[i], mul(1, dx[i], X), X);
      y[i] = add(y[i], mul(1, dy[i], Y), Y);
    }
    int total_dist = 0LL;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        total_dist += (llint)abs(x[i] - x[j]) + abs(y[i] - y[j]);
      }
    }

    if (total_dist < best) {
      best = total_dist;
      print();
      printf("%d\n", t + 1);
    }
  }

  return 0;
}
