#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int G[101][101][101];

int main() {
  memset(G, 0, sizeof G);
  
  char s[1024];
  int x1, x2;
  int y1, y2;
  int z1, z2;
  while (scanf(" %s x=%d..%d,y=%d..%d,z=%d..%d\n", s, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
    if (x1 > x2)
      swap(x1, x2);
    if (y1 > y2)
      swap(y1, y2);
    if (z1 > z2)
      swap(z1, z2);
    for (int i=max(x1, -50); i<=min(x2, 50); i++)
      for (int j=max(y1, -50); j<=min(y2, 50); j++)
        for (int k=max(z1, -50); k<=min(z2, 50); k++)
            G[i+50][j+50][k+50] = s[1] == 'n';
  }

  int cnt = 0;
  for (int i=0; i<100; i++)
    for (int j=0; j<100; j++)
      for (int k=0; k<100; k++)
        cnt += G[i][j][k];

  cout << cnt << endl;
        
  return 0;
}
