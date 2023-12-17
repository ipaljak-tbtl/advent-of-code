#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;
const int INF = 1e9 + 10;

// RDLU
const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

char grid[MAXN][MAXN];

int n;
int dist[MAXN][MAXN][5][11];

struct Node {
  int r, s, dir, step, d;

  Node() {}
  Node(int r, int s, int dir, int step, int d): r(r), s(s), dir(dir), step(step), d(d) {}

  friend bool operator < (const Node &A, const Node &B) {
    return A.d > B.d;
  }

  bool visited() const {
    return dist[r][s][dir][step] != -1;
  }

  void set_dist() {
    dist[r][s][dir][step] = d;
  }
};

inline bool check(const int r, const int s) {
  return min(r, s) >= 0 && max(r, s) < n;
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1);
  n -= 1;

  memset(dist, -1, sizeof dist);
  Node curr(0, 0, 0, 10, 0);

  priority_queue<Node> pq;
  pq.push(curr);

  int sol = INF;
  while (!pq.empty()) {
    while (!pq.empty() && pq.top().visited()) pq.pop();
    if (pq.empty()) break;

    auto curr = pq.top();
    if (curr.r == n - 1 && curr.s == n - 1 && curr.step <= 6)
      sol = min(sol, curr.d);
    curr.set_dist();
    pq.pop();

    for (int k : {(curr.dir + 3) % 4, curr.dir, (curr.dir + 1) % 4}) {
      int rr = curr.r + dr[k], ss = curr.s + ds[k];
      if (!check(rr, ss)) continue;
      if (k != curr.dir && curr.step <= 6) {
        auto nxt = Node(rr, ss, k, 9, curr.d + grid[rr][ss] - '0');
        if (!nxt.visited()) pq.push(nxt);
        continue;
      }
      if (k != curr.dir) continue;
      if (curr.step == 0) continue;
      auto nxt = Node(rr, ss, k, curr.step - 1, curr.d + grid[rr][ss] - '0');
      if (!nxt.visited()) pq.push(nxt);
    }
  }

  printf("%d\n", sol);
  return 0;
}
