#include <bits/stdc++.h>

using namespace std;

char dummy_str[10];

int get_value() {
  set<int> win;
  for (int i = 0; i < 10; ++i) {
    int x;
    scanf("%d", &x);
    win.insert(x);
  }

  scanf("%s", dummy_str);

  int ret = 0;
  for (int i = 0; i < 25; ++i) {
    int x;
    scanf("%d", &x);
    ret += win.find(x) != win.end();
  }

  if (ret == 0)
    return ret;
  return 1 << (ret - 1);
}

int main(void) {
  int card_id, sol = 0;
  while (scanf("%s %d:", dummy_str, &card_id) == 2)
    sol += get_value();

  printf("%d\n", sol);
  return 0;
}
