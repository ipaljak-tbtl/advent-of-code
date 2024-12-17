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

const int MAXN = 155;

const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

struct Node {
  int r, s, dir, dist;

  Node() {}
  Node(int r, int s, int dir, int dist) : r(r), s(s), dir(dir), dist(dist) {}

  friend bool operator<(const Node &A, const Node &B) {
    return A.dist > B.dist;
  }
};

bool bio[MAXN][MAXN][5];

char grid[MAXN][MAXN];

int r, s;
int dist[MAXN][MAXN][5];

inline bool check(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s && grid[rr][ss] != '#';
}

int dijkstra_se() {
  priority_queue<Node> pq;
  memset(dist, -1, sizeof dist);

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] == 'S')
        pq.push(Node(i, j, 0, 0));

  while (!pq.empty()) {
    while (!pq.empty() && dist[pq.top().r][pq.top().s][pq.top().dir] != -1)
      pq.pop();
    if (pq.empty())
      break;

    Node curr = pq.top();
    dist[curr.r][curr.s][curr.dir] = curr.dist;
    pq.pop();

    for (int di : {0, -1, 1}) {
      int nr = curr.r + dr[(curr.dir + di + 4) % 4] * (1 - abs(di));
      int ns = curr.s + ds[(curr.dir + di + 4) % 4] * (1 - abs(di));
      if (!check(nr, ns))
        continue;
      Node nxt(nr, ns, (curr.dir + di + 4) % 4, curr.dist + 1 + 999 * abs(di));
      pq.push(nxt);
    }
  }

  int ret = 1e9 + 10;

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      for (int dir = 0; dir < 4; ++dir)
        if (grid[i][j] == 'E' && dist[i][j][dir] != -1)
          ret = min(ret, dist[i][j][dir]);

  return ret;
}

int dijkstra_es(int best) {
  set<pair<int, int>> chairs;
  priority_queue<Node> pq;

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      for (int dir = 0; dir < 4; ++dir)
        if (grid[i][j] == 'E')
          pq.push(Node(i, j, dir, 0));

  while (!pq.empty()) {
    while (!pq.empty() && bio[pq.top().r][pq.top().s][pq.top().dir])
      pq.pop();
    if (pq.empty())
      break;

    Node curr = pq.top();
    bio[curr.r][curr.s][curr.dir] = true;
    if (best == curr.dist + dist[curr.r][curr.s][(curr.dir + 2) % 4])
      chairs.insert({curr.r, curr.s});
    pq.pop();

    for (int di : {0, -1, 1}) {
      int nr = curr.r + dr[(curr.dir + di + 4) % 4] * (1 - abs(di));
      int ns = curr.s + ds[(curr.dir + di + 4) % 4] * (1 - abs(di));
      if (!check(nr, ns))
        continue;
      Node nxt(nr, ns, (curr.dir + di + 4) % 4, curr.dist + 1 + 999 * abs(di));
      pq.push(nxt);
    }
  }

  return (int)chairs.size();
}

int main(void) {
  while (scanf("%s", grid[r]) == 1)
    ++r;
  s = strlen(grid[0]);

  int best = dijkstra_se();
  printf("%d\n", dijkstra_es(best));

  return 0;
}
