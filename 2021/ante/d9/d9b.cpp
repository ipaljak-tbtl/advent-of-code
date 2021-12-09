#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

vector<vector<int>> done;
vector<string> height;
int n, m;

int visit(int x, int y) {
  if (x < 0 || x > n-1 || y < 0 || y > m-1)
    return 0;
  if (height[x][y] == '9')
    return 0;
  if (done[x][y])
    return 0;
  done[x][y] = 1;
  return 1+visit(x-1, y)+visit(x+1, y)+visit(x, y-1)+visit(x, y+1);
}

int main() {
  string line;
  while (cin >> line)
    height.push_back(line);

  n = height.size();
  m = height[0].size();
  done = vector<vector<int>>(n, vector<int>(m, 0));
  vector<int> basins;
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++) 
      if (!done[i][j])
        basins.push_back(visit(i, j));

  assert((int)basins.size() >= 3);
  sort(basins.begin(), basins.end(), greater<int>());
  cout << basins[0]*basins[1]*basins[2] << endl;
  
  return 0;
}
