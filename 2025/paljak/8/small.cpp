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

struct DSU {
  vector<int> parent, size;

  DSU(int n) : parent(n), size(n, 1) {
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find_set(int x) {
    if (parent[x] == x)
      return x;
    return parent[x] = find_set(parent[x]);
  }

  void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x == y)
      return;

    if (size[x] > size[y])
      swap(x, y);

    size[y] += size[x];
    parent[x] = y;
  }
};

struct Point {
  int x, y, z;
  Point() {}
  Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

int n;
vector<Point> p;

struct Line {
  int a, b;
  Line() {}
  Line(int a, int b) : a(a), b(b) {}
  llint dsq() const {
    return (llint)(p[a].x - p[b].x) * (p[a].x - p[b].x) +
           (llint)(p[a].y - p[b].y) * (p[a].y - p[b].y) +
           (llint)(p[a].z - p[b].z) * (p[a].z - p[b].z);
  }
  friend bool operator<(const Line &l1, const Line &l2) {
    return l1.dsq() < l2.dsq();
  }
};

vector<Line> l;

int main(void) {
  int x, y, z;
  while (scanf("%d,%d,%d", &x, &y, &z) != EOF)
    p.emplace_back(x, y, z);

  n = (int)p.size();

  TRACE(n);
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      l.emplace_back(i, j);

  sort(l.begin(), l.end());

  DSU dsu(n);
  for (int i = 0; i < 1000; ++i)
    dsu.union_sets(l[i].a, l[i].b);

  set<pair<int, int>> circ;
  for (int i = 0; i < n; ++i)
    circ.insert({dsu.size[dsu.find_set(i)], dsu.find_set(i)});

  int sol = 1;
  auto it = circ.rbegin();
  for (int i = 0; i < 3; ++i, ++it)
    sol *= it->first;

  printf("%d\n", sol);
  return 0;
}
