#include <bits/stdc++.h>

using namespace std;

vector<int> input() {
  vector<int> ret;
  int el;
  while (scanf("%d", &el) != EOF)
    ret.emplace_back(el);
  return ret;
}

int main(void) {
  vector<int> report = input();

  int sol = 0;
  for (int i = 1; i < (int)report.size(); ++i)
    sol += report[i] > report[i - 1];

  printf("%d\n", sol);

  return 0;
}
