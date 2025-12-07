#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

vector<pair<llint, llint>> ranges;


int main() {
  llint x, y;
  while (scanf("%lld-%lld", &x, &y) == 2)
    ranges.push_back({x, y});

  sort(ranges.begin(), ranges.end());

  llint total = 0;
  llint position = 0;
  llint end = -1;
  
  for (auto [x, y] : ranges) {
    if (end != -1 && end < x)
      total += end - position + 1;
    else if (end >= x)
      total += x - position;
    position = x;
    end = max(end, y);
  }
  total += end - position + 1;

  cout << total << endl;
}
