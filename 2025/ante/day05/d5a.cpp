#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

vector<llint> lo;
vector<llint> hi;


int is_fresh(llint x) {
  for (int i = 0; i < (int)lo.size(); i++)
    if (lo[i] <= x && x <= hi[i])
      return 1;
  return 0;
} 


int main() {
  llint x, y;
  while (scanf("%lld-%lld", &x, &y) == 2) {
    lo.push_back(x);
    hi.push_back(y);
  }

  int total = 0;
  do {
    if (is_fresh(x))
      total++;
  } while (scanf("%lld", &x) == 1);

  printf("%d\n", total);
  return 0;
}
