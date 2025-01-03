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

// const int N = 7;
// const int M = 12;

const int N = 71;
const int M = 1024;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

char grid[N][N];
int dist[N][N];

vector<int> xs, ys;

inline void init() {
  memset(grid, '.', sizeof grid);
  memset(dist, -1, sizeof dist);
}

inline bool check(int r, int s) {
  return r >= 0 && r < N && s >= 0 && s < N && grid[r][s] != '#' &&
         dist[r][s] == -1;
}

bool bfs(int sz) {
  init();
  for (int i = 0; i <= sz; ++i)
    grid[ys[i]][xs[i]] = '#';

  queue<pair<int, int>> q;
  q.push({0, 0});
  dist[0][0] = 0;

  while (!q.empty()) {
    const auto curr = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int r = curr.first + dr[i], s = curr.second + ds[i];
      if (!check(r, s))
        continue;
      dist[r][s] = dist[curr.first][curr.second] + 1;
      q.push({r, s});
    }
  }

  return dist[N - 1][N - 1] != -1;
}

int main(void) {
  int x, y;
  while (scanf("%d,%d", &x, &y) == 2) {
    xs.push_back(x);
    ys.push_back(y);
  }

  int lo = 0, hi = (int)xs.size() - 1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (bfs(mid))
      lo = mid + 1;
    else
      hi = mid;
  }

  TRACE(lo _ bfs(lo - 1) _ bfs(lo));
  printf("%d,%d\n", xs[lo], ys[lo]);

  return 0;
}
