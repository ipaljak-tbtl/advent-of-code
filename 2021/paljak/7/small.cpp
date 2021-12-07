#include <bits/stdc++.h>

using namespace std;

vector<int> pos;

int main(void) {
  int x;
  scanf("%d", &x);
  pos.push_back(x);
  while (scanf(",%d", &x) == 1)
    pos.push_back(x);

  sort(pos.begin(), pos.end());

  int sol = 0;
  for (int curr : pos)
    sol += abs(curr - pos[pos.size() / 2]);

  printf("%d\n", sol);
  return 0;
}
