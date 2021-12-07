#include <bits/stdc++.h>

using namespace std;

vector<int> pos;

int fuel(int t) {
  int ret = 0;
  for (int x : pos)
    ret += abs(x - t) * (abs(x - t) + 1) / 2;
  return ret;
}

int main(void) {
  int x;
  scanf("%d", &x);
  pos.push_back(x);
  while (scanf(",%d", &x) == 1)
    pos.push_back(x);

  int sum = 0, n = (int)pos.size();
  for (int x : pos) sum += x;

  printf("%d\n", min(fuel(sum / n), fuel(sum / n + 1)));
  return 0;
}
