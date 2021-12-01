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
  int prev_window = report[0] + report[1] + report[2];
  for (int i = 3; i < (int)report.size(); ++i) {
    int curr_window = prev_window + report[i] - report[i - 3];
    sol += curr_window > prev_window;
    prev_window = curr_window;
  }

  printf("%d\n", sol);

  return 0;
}
