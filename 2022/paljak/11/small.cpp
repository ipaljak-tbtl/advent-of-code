#include <bits/stdc++.h>

using namespace std;

struct Monkey {
  int inspected = 0;
  queue<int> items;
  string oper, arg1, arg2;
  int div_test, true_dest, false_dest;

  void add_item(int worry) {
    items.push(worry);
  }

  pair<int, int> inspect() {
    if (items.empty()) return {-1, -1};
    ++inspected;
    int worry = items.front();
    items.pop();
    int new_worry = calc_worry(worry) / 3;
    if (new_worry % div_test == 0)
      return {true_dest, new_worry};
    else
      return {false_dest, new_worry};
  }

  int calc_worry(int old) {
    int a = 0, b = 0;
    if (arg1 != "old") a = stoi(arg1); else a = old;
    if (arg2 != "old") b = stoi(arg2); else b = old;
    if (oper == "+") return a + b;
    if (oper == "*") return a * b;
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
    ret.add_item(worry);
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

  for (int round = 0; round < 20; ++round) {
    for (auto &m : monkey) {
      pair<int, int> p;
      while ((p = m.inspect()) != make_pair(-1, -1))
        monkey[p.first].add_item(p.second);
    }
  }

  sort(monkey.begin(), monkey.end(), [](const Monkey &A, const Monkey &B) {
    return A.inspected > B.inspected;
  });

  cout << monkey[0].inspected * monkey[1].inspected << endl;
  return 0;
}
