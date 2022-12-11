#include <bits/stdc++.h>

using namespace std;

long long M = 1;

struct Monkey {
  int inspected = 0;
  queue<long long> items;
  string oper, arg1, arg2;
  int div_test, true_dest, false_dest;

  void add_item(long long worry) {
    items.push(worry % M);
  }

  pair<int, long long> inspect() {
    if (items.empty()) return {-1, -1};
    ++inspected;
    long long worry = items.front();
    items.pop();
    long long new_worry = calc_worry(worry); // / 3;
    if (new_worry % (long long) div_test == 0)
      return {true_dest, new_worry};
    else
      return {false_dest, new_worry};
  }

  long long calc_worry(long long old) {
    long long a = 0, b = 0;
    if (arg1 != "old") a = stoll(arg1); else a = old;
    if (arg2 != "old") b = stoll(arg2); else b = old;
    if (oper == "+") return (a + b) % M;
    if (oper == "*") return (a * b) % M;
    assert(false);
  }
};

vector<Monkey> monkey;

Monkey read_monkey() {
  Monkey ret;
  string s;
  cin >> s >> s;
  while (true) {
    int worry;
    cin >> worry;
    ret.add_item((long long) worry);
    if (cin.peek() != ',') break;
    char c; cin >> c;
  }
  cin >> s >> s >> s;
  cin >> ret.arg1 >> ret.oper >> ret.arg2;
  cin >> s >> s >> s;
  cin >> ret.div_test;
  cin >> s >> s >> s >> s >> s;
  cin >> ret.true_dest;
  cin >> s >> s >> s >> s >> s;
  cin >> ret.false_dest;
  return ret;
}

int main(void) {
  string s;
  while (cin >> s) {
    if (s != "Monkey") break;
    cin >> s;
    monkey.emplace_back(read_monkey());
  }

  for (auto &m : monkey) M *= (long long) m.div_test;

  for (int round = 0; round < 10000; ++round) {
    for (auto &m : monkey) {
      pair<int, long long> p;
      while ((p = m.inspect()) != make_pair(-1, (long long)-1))
        monkey[p.first].add_item(p.second);
    }
  }

  sort(monkey.begin(), monkey.end(), [](const Monkey &A, const Monkey &B) {
    return A.inspected > B.inspected;
  });

  cout << (long long) monkey[0].inspected * monkey[1].inspected << endl;
  return 0;
}
