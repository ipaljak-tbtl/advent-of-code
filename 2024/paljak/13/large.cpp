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

const llint OFFSET = 10000000000000LL;

llint ax, ay, bx, by, x, y, sol;

llint det(llint a, llint b, llint c, llint d) { return a * d - c * b; }

llint calc(llint ax, llint ay, llint bx, llint by, llint x, llint y) {
  assert(det(ax, bx, ay, by) != 0);
  llint A = det(x, bx, y, by) / det(ax, bx, ay, by);
  llint B = det(ax, x, ay, y) / det(ax, bx, ay, by);
  if (A * ax + B * bx != x || A * ay + B * by != y)
    return 0;
  return 3 * A + B;
}

int main(void) {
  while (scanf("Button A: X+%lld, Y+%lld\n", &ax, &ay) == 2) {
    scanf("Button B: X+%lld, Y+%lld\n", &bx, &by);
    scanf("Prize: X=%lld, Y=%lld\n", &x, &y);
    x += OFFSET;
    y += OFFSET;
    sol += calc(ax, ay, bx, by, x, y);
  }

  printf("%lld\n", sol);
  return 0;
}
