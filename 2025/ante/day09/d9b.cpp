#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

int n;
vector<int> x;
vector<int> y;

bool check_special() {
  vector<int> xx = x;
  sort(xx.begin(), xx.end());
  for (int i = 1; i < n-2; i++)
      if (xx[i]+1 >= xx[i+2]) {
      printf("x %d %d %d\n", xx[i], xx[i+1], xx[i+2]);
      return false;
    }
  return true;
}

bool cuts_inside(int xlo, int xhi, int ylo, int yhi) {
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    int xxlo = min(x[i], x[j]);
    int xxhi = max(x[i], x[j]);
    int yylo = min(y[i], y[j]);
    int yyhi = max(y[i], y[j]);
    int ixlo = max(xlo+1, xxlo);
    int ixhi = min(xhi-1, xxhi);
    int iylo = max(ylo+1, yylo);
    int iyhi = min(yhi-1, yyhi);
    if (ixlo <= ixhi && iylo <= iyhi)
      return true;
  }
  return false;
}

int main() {
  int a, b;
  while (scanf("%d,%d", &a, &b) == 2) {
    x.push_back(a);
    y.push_back(b);
  }
  n = (int)x.size();

  assert(check_special());

  llint best = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      int xlo = min(x[i], x[j]);
      int xhi = max(x[i], x[j]);
      int ylo = min(y[i], y[j]);
      int yhi = max(y[i], y[j]); 
      if (cuts_inside(xlo, xhi, ylo, yhi))
        continue ;
      llint dx = abs(xhi - xlo)+1;
      llint dy = abs(yhi - ylo)+1;
      llint area = dx * dy;
      best = max(best, area);
    }
  printf("%lld\n", best);
  
  return 0;
}
