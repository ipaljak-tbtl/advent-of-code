#include <bits/stdc++.h>

using namespace std;

int el_cnt[27];

string temp;

map<string, int> cnt;
map<string, string> rules;

inline void parse_template() {
  cin >> temp;
  for (int i = 1; i < temp.size(); ++i)
    cnt[temp.substr(i - 1, 2)]++;
}

inline void parse_rules() {
  string a, b, c;
  while (cin >> a >> b >> c) {
    assert(rules.find(a) == rules.end());
    rules[a] = c;
  }
}

void step() {
  map<string, int> new_cnt;
  for (auto &p : cnt) {
    if (rules.find(p.first) == rules.end()) {
      new_cnt[p.first] += p.second;
      continue;
    }
    auto r = rules[p.first];
    string a = { p.first[0], r[0] };
    string b = { r[0], p.first[1] };
    new_cnt[a] += p.second;
    new_cnt[b] += p.second;
  }
  cnt = new_cnt;
}

int main(void) {
  parse_template();
  parse_rules();

  for (int i = 0; i < 10; ++i)
    step();

  el_cnt[temp[0] - 'A']++;
  el_cnt[temp[temp.size() - 1] - 'A']++;
  for (auto &p : cnt) {
    el_cnt[p.first[0] - 'A'] += p.second;
    el_cnt[p.first[1] - 'A'] += p.second;
  }

  sort(el_cnt, el_cnt + 26);
  int mx = el_cnt[25] / 2, mn = el_cnt[25] / 2;
  for (int i = 25; i >= 0 && el_cnt[i] != 0; --i)
    mn = el_cnt[i] / 2;

  cout << mx - mn << endl;

  return 0;
}
