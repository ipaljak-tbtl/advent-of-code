#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

const string TARGET = "XMAS";

int m;
int n;
vector<string> grid;


int find(int x, int y) {
  if (grid[x][y] != 'A')
    return 0;
  string s1 = string()+grid[x-1][y-1]+grid[x+1][y+1];
  string s2 = string()+grid[x-1][y+1]+grid[x+1][y-1];
  if (s1 != "SM" && s1 != "MS")
    return 0;
  if (s2 != "SM" && s2 != "MS")
    return 0;
  return 1;
}


int main() {
  string s;
  while (cin >> s)
    grid.push_back(s);
  m = grid.size();
  n = grid[0].size();

  int total = 0;
  for (int i=1; i<m-1; i++)
    for (int j=1; j<n-1; j++)
      if (find(i, j))
        total++;

  cout << total << endl;
  return 0;
}
