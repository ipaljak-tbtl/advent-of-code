#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  vector<string> map;
  string line;
  while (cin >> line)
    map.push_back(line);

  int n = map.size();
  int m = map[0].size();
  int total = 0;
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++) {
      int is_min = 1;
      if (i > 0 && map[i-1][j] <= map[i][j])
        is_min = 0;
      if (j > 0 && map[i][j-1] <= map[i][j])
        is_min = 0;
      if (i < n-1 && map[i+1][j] <= map[i][j])
        is_min = 0;
      if (j < m-1 && map[i][j+1] <= map[i][j])
        is_min = 0;
      if (is_min)
        total += map[i][j]-'0'+1;
    }
  cout << total << endl;
  
  return 0;
}
