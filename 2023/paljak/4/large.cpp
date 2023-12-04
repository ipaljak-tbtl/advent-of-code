#include <bits/stdc++.h>

using namespace std;

int cnt[300];
char dummy_str[10];

int get_value(int card_id) {
  ++cnt[card_id];
  set<int> win;
  for (int i = 0; i < 10; ++i) {
    int x;
    scanf("%d", &x);
    win.insert(x);
  }

  scanf("%s", dummy_str);

  int wins = 0;
  for (int i = 0; i < 25; ++i) {
    int x;
    scanf("%d", &x);
    wins += win.find(x) != win.end();
  }

  for (int i = 0; i < wins; ++i)
    cnt[card_id + i + 1] += cnt[card_id];

  return cnt[card_id];
}

int main(void) {
  int card_id, sol = 0;
  while (scanf("%s %d:", dummy_str, &card_id) == 2)
    sol += get_value(card_id);

  printf("%d\n", sol);
  return 0;
}
