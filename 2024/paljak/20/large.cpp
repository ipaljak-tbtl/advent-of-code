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

const int MAXN = 150;

const int CHEAT_TIME = 20;
const int THRESHOLD = 100;

const int dr[] = {1, 0, -1, 0};
const int ds[] = {0, 1, 0, -1};

char grid[MAXN][MAXN];

int r, s;
int dist_s[MAXN][MAXN], dist_e[MAXN][MAXN];

inline bool check(int rr, int ss) {
  return rr >= 0 && rr < r && ss >= 0 && ss < s && grid[rr][ss] != '#';
}

void bfs(int start_r, int start_s, int (&dist)[MAXN][MAXN]) {
  TRACE(start_r _ start_s);
  memset(dist, -1, sizeof dist);
  queue<pair<int, int>> q;
  q.push({start_r, start_s});
  dist[start_r][start_s] = 0;

  while (!q.empty()) {
    auto &p = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      int rr = p.first + dr[i], ss = p.second + ds[i];
      if (!check(rr, ss) || dist[rr][ss] != -1)
        continue;
      dist[rr][ss] = dist[p.first][p.second] + 1;
      q.push({rr, ss});
    }
  }
}

int main(void) {
  while (scanf("%s", grid[r]) == 1)
    ++r;
  s = strlen(grid[0]);

  TRACE(r _ s);

  int er, es;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (grid[i][j] == 'S')
        bfs(i, j, dist_s);
      if (grid[i][j] == 'E') {
        bfs(i, j, dist_e);
        er = i, es = j;
      }
    }
  }

  int best = dist_s[er][es];
  int sol = 0;

  TRACE(best);

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (dist_s[i][j] == -1)
        continue;
      for (int ii = 0; ii < r; ++ii) {
        for (int jj = 0; jj < s; ++jj) {
          if (dist_e[ii][jj] == -1)
            continue;
          if (abs(i - ii) + abs(j - jj) > CHEAT_TIME)
            continue;
          int save =
              best - dist_s[i][j] - dist_e[ii][jj] - abs(i - ii) - abs(j - jj);
          sol += save >= THRESHOLD;
        }
      }
    }
  }

  printf("%d\n", sol);

  return 0;
}
