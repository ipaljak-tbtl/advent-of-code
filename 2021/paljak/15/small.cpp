#include <bits/stdc++.h>

using namespace std;

struct Node {
  int r, s, dist;

  Node() {}
  Node(int r, int s, int dist) : r(r), s(s), dist(dist) {}

  friend bool operator<(const Node &A, const Node &B) {
    return A.dist > B.dist;
  }
};

const int MAXN = 1010;
const int dr[] = {0, 1, 0, -1};
const int ds[] = {1, 0, -1, 0};

int n;
int d[MAXN][MAXN];

char grid[MAXN][MAXN];

inline bool check(int r, int s) {
  return r >= 0 && r < n && s >= 0 && s < n && d[r][s] == -1;
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1)
    ;
  --n;

  priority_queue<Node> pq;
  memset(d, -1, sizeof d);

  pq.push(Node(0, 0, 0));
  while (!pq.empty()) {
    while (!pq.empty() && d[pq.top().r][pq.top().s] != -1) pq.pop();
    if (pq.empty()) break;

    auto curr = pq.top();
    pq.pop();

    d[curr.r][curr.s] = curr.dist;
    for (int i = 0; i < 4; ++i) {
      int r = curr.r + dr[i], s = curr.s + ds[i];
      if (!check(r, s)) continue;
      pq.push(Node(r, s, curr.dist + grid[r][s] - '0'));
    }
  }

  printf("%d\n", d[n - 1][n - 1]);

  return 0;
}
