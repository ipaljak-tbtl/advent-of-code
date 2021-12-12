#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int n;
int m;
vector<string> L;


int step() {
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      L[i][j]++;
  
  queue<pair<int, int>> Q;
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      if (L[i][j] > '9')
        Q.push({i, j});

  int count = 0;
  while (!Q.empty()) {
    auto [x, y] = Q.front();
    Q.pop();
    if (L[x][y] == '0')
      continue ;
    L[x][y] = '0';
    count++;
    for (int xx=x-1; xx<=x+1; xx++)
      for (int yy=y-1; yy<=y+1; yy++) {
        if (xx < 0 || xx >=n || yy < 0 || yy >= m)
          continue ;
        if (L[xx][yy] == '0')
          continue ;
        L[xx][yy]++;
        if (L[xx][yy] > '9')
          Q.push({xx, yy});
      }
  }
  
  return count;
}

int main() {
  string line;
  while (cin >> line)
    L.push_back(line);
  n = L.size();
  m = L[0].size();
  
  int total = 0;
  for (int i=0; i<100; i++)
    total += step();
  
  cout << total << endl;
      
  return 0;
}
