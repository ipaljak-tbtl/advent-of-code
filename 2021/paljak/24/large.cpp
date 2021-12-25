#include <bits/stdc++.h>

typedef long long llint;

using namespace std;

struct Command {
  string type, op1, op2;

  Command() {}
  Command(string type, string op1, string op2) : type(type), op1(op1), op2(op2) {}
};

struct ALU {
  bool invalid = false;
  llint x, y, z, w;

  ALU() {};
  ALU(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}

  void execute(const Command &C) {
    if (invalid) return;
    llint o1 = get_val(C.op1);
    llint o2 = get_val(C.op2);
    llint ret = 0;
    if (C.type == "add") ret = o1 + o2;
    if (C.type == "mul") ret = o1 * o2;
    if (C.type == "div") {
      if (o2 == 0) { invalid = true; return; }
      ret = o1 / o2;
    }
    if (C.type == "mod") {
      if (o1 < 0 || o2 <= 0) { invalid = true; return; }
      ret = o1 % o2;
    }
    if (C.type == "eql") ret = o1 == o2;
    store(C.op1, ret);
  }

  llint get_val(const string &reg) {
    if (reg[0] == '-' || (reg[0] >= '0' && reg[0] <= '9')) {
      llint ret = 0;
      for (char c : reg) {
        if (c == '-') continue;
        ret *= 10LL;
        ret += (llint) c - '0';
      }
      if (reg[0] == '-') ret *= -1;
      return ret;
    }
    if (reg == "x") return x;
    if (reg == "y") return y;
    if (reg == "z") return z;
    if (reg == "w") return w;
    assert(false);
  }

  void store(const string &reg, llint val) {
    if (reg == "x") { x = val; return; }
    if (reg == "y") { y = val; return; }
    if (reg == "z") { z = val; return; }
    if (reg == "w") { w = val; return; }
    assert(false);
  }

};

vector<Command> command;

map<pair<int, llint>, string> memo;

inline void read() {
  string type, op1, op2;
  while (cin >> type) {
    cin >> op1;
    if (type != "inp")
      cin >> op2;
    else
      op2 = "<empty>";
    command.emplace_back(type, op1, op2);
  }
}

llint eval(int step, llint prev_z, llint curr_w) {
  ALU alu(0, 0, prev_z, curr_w);
  for (int i = step * 18 + 1; i < (step + 1) * 18; ++i)
    alu.execute(command[i]);
  if (alu.invalid) return -123456789LL;
  return alu.z;
}

string solve(int step, llint prev_z) {
  if (memo.find({step, prev_z}) != memo.end())
    return memo[{step, prev_z}];
  if (step == 14) {
    if (prev_z == 0) return memo[{step, prev_z}] = "";
    return memo[{step, prev_z}] = "$";
  }

  string ret = "$";
  for (int i = 1; i <= 9; ++i) {
    llint next_z = eval(step, prev_z, i);
    if (next_z == -123456789LL) continue;
    string suff = solve(step + 1, next_z);
    if (suff == "$") continue;
    ret = "";
    ret.push_back('0' + i);
    ret += suff;
    break;
  }

  return memo[{step, prev_z}] = ret;
}

int main(void) {
  read();

  cout << solve(0, 0) << endl;

  return 0;
}
