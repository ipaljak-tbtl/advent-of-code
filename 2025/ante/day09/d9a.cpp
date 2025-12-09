#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

int n;
vector<int> x;
vector<int> y;

int main() {
  int a, b;
  while (scanf("%d,%d", &a, &b) == 2) {
    x.push_back(a);
    y.push_back(b);
  }
  n = (int)x.size();

  llint best = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      llint dx = abs(x[j] - x[i])+1;
      llint dy = abs(y[j] - y[i])+1;
      llint area = dx * dy;
      best = max(best, area);
    }
  printf("%lld\n", best);

  return 0;
}
