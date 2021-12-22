#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

unsigned long long D[2][10][22][22];

int main() {
  int p[2] = {0, 0};
  scanf("Player 1 starting position: %d\n", &p[0]);
  scanf("Player 2 starting position: %d\n", &p[1]);
  p[0]--;
  p[1]--;
  memset(D, 0, sizeof D);
  D[0][p[0]][0][0] = 1ll;
  D[1][p[1]][0][0] = 1ll;
  for (int k=0; k<22; k++) 
    for (int x=0; x<10; x++)
      for (int s=0; s<21; s++) {
        D[(k+1)%2][x][s][k+1] = D[(k+1)%2][x][s][k];
        for (int i1=1; i1<=3; i1++)
          for (int i2=1; i2<=3; i2++)
            for (int i3=1; i3<=3; i3++) {
              int nx = (x+i1+i2+i3)%10;
              int ns = min(21, s+nx+1);
              D[k%2][nx][ns][k+1] += D[k%2][x][s][k];
            }
      }

  unsigned long long total[2] = {0, 0};
  for (int k=0; k<21; k++)
    for (int x=0; x<10; x++)
      for (int y=0; y<10; y++)
        for (int s=0; s<21; s++)
          total[k%2] += D[k%2][x][21][k+1]*D[(k+1)%2][y][s][k];

  cout << max(total[0], total[1]) << endl;
        
  return 0;
}
