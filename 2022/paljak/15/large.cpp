#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;
const int MAXCOR = 4000000;
//const int MAXCOR = 20;

int n;
int sx[MAXN], sy[MAXN], bx[MAXN], by[MAXN];

int main(void) {
  while (scanf("Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &sx[n], &sy[n], &bx[n], &by[n]) != EOF)
    ++n;

  for (int y = 0; y <= MAXCOR; ++y) {
    vector<pair<int, int>> v;
    for (int i = 0; i < n; ++i) {
      int k = abs(sx[i] - bx[i]) + abs(sy[i] - by[i]) - abs(y - sy[i]);
      if (k < 0) continue;
      v.emplace_back(sx[i] - k, sx[i] + k);
    }

    sort(v.begin(), v.end());
    int maxx = v[0].second;
    for (auto &p : v) {
      if (p.first > maxx) {
        printf("%lld\n", (long long)(p.first - 1) * MAXCOR + y);
        exit(0);
      }
      maxx = max(maxx, p.second);
    }
  }

  return 0;
}
