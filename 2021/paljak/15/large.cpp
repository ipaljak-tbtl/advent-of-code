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
  return r >= 0 && r < 5 * n && s >= 0 && s < 5 * n && d[r][s] == -1;
}

inline int get_val(int r, int s) {
  return 1 + ((grid[r % n][s % n] - '0' - 1) + r / n + s / n) % 9;
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
      pq.push(Node(r, s, curr.dist + get_val(r, s)));
    }
  }

  printf("%d\n", d[5 * n - 1][5 * n - 1]);

  return 0;
}
