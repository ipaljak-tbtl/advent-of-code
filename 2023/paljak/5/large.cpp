#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 25;
const int MAXM = 10;

const llint UPPER_BOUND = 359042615LL; // Obtained from part 1

struct transition {
  llint lo, val, len;
  transition() {}
  transition(llint lo, llint val, llint len): lo(lo), val(val), len(len) {}
};

int n, m;
llint seeds[MAXN];

vector<vector<transition>> ts;

llint find_seed(llint loc) {
  llint ret = loc;
  for (const auto &trans : ts) {
    for (const auto &t : trans) {
      if (t.lo <= ret && ret < t.lo + t.len) {
        ret = t.val + (ret - t.lo);
        break;
      }
    }
  }
  return ret;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%lld", &seeds[i]);

  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int sz;
    scanf("%d", &sz);
    vector<transition> t;
    for (int j = 0; j < sz; ++j) {
      llint lo, val, len;
      scanf("%lld%lld%lld", &lo, &val, &len);
      t.emplace_back(lo, val, len);
    }
    ts.emplace_back(t);
  }

  reverse(ts.begin(), ts.end());

  for (llint loc = 0; loc <= UPPER_BOUND; ++loc) {
    llint seed = find_seed(loc);
    bool ok = false;
    for (int i = 0; i < n; i += 2)
      ok |= seeds[i] <= seed && seed < seeds[i] + seeds[i + 1];
    if (ok) {
      printf("%lld\n", loc);
      break;
    }
  }

  return 0;
}
