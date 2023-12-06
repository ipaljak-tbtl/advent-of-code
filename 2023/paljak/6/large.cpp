#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

int main(void) {
  llint t, d;
  scanf("%lld%lld", &t, &d);

  llint sol = 0;
  for (llint s = 0; s < t; ++s) {
    llint dist = (t - s) * s;
    sol += dist > d;
  }

  printf("%lld\n", sol);

  return 0;
}
