#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <class T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

#define TRACE(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#define _ << " _ " <<

template <class T, class U> ostream &operator<<(ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}
template <class> struct is_container : false_type {};
template <class... Ts> struct is_container<vector<Ts...>> : true_type {};
template <class... Ts> struct is_container<map<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template <class... Ts> struct is_container<set<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template <class... Ts> struct is_container<multiset<Ts...>> : true_type {};
template <class... Ts>
struct is_container<unordered_multiset<Ts...>> : true_type {};
template <class T, class = typename enable_if<is_container<T>::value>::type>
ostream &operator<<(ostream &o, T x) {
  int f = 1;
  o << "{";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "}";
}

typedef long long llint;

int ip;
llint ra, rb, rc;

vector<int> prog, out_buff;

llint literal_operand(int adr) { return (llint)prog[adr]; }

llint combo_operand(int adr) {
  if (prog[adr] <= 3)
    return (llint)prog[adr];
  if (prog[adr] == 4)
    return ra;
  if (prog[adr] == 5)
    return rb;
  if (prog[adr] == 6)
    return rc;
  assert(false);
}

void execute() {
  if (prog[ip] == 0) {
    ra = ra / (1LL << combo_operand(ip + 1));
    ip += 2;
    return;
  }

  if (prog[ip] == 1) {
    rb = rb ^ literal_operand(ip + 1);
    ip += 2;
    return;
  }

  if (prog[ip] == 2) {
    rb = combo_operand(ip + 1) % 8;
    ip += 2;
    return;
  }

  if (prog[ip] == 3) {
    if (ra == 0)
      ip += 2;
    else
      ip = literal_operand(ip + 1);
    return;
  }

  if (prog[ip] == 4) {
    rb ^= rc;
    ip += 2;
    return;
  }

  if (prog[ip] == 5) {
    out_buff.push_back((int)(combo_operand(ip + 1) % 8));
    ip += 2;
    return;
  }

  if (prog[ip] == 6) {
    rb = ra / (1LL << combo_operand(ip + 1));
    ip += 2;
    return;
  }

  if (prog[ip] == 7) {
    rc = ra / (1LL << combo_operand(ip + 1));
    ip += 2;
    return;
  }

  assert(false);
}

void run_prog(llint a) {
    ra = a;
    rb = rc = ip = 0;
    out_buff.clear();
    while (ip < prog.size() - 1)
      execute();
}

int main(void) {
  scanf("Register A: %lld\n", &ra);
  scanf("Register B: %lld\n", &rb);
  scanf("Register C: %lld\n\n", &rc);

  int x;
  scanf("Program: %d", &x);
  prog.push_back(x);
  while (scanf(",%d", &x) == 1)
    prog.push_back(x);

  TRACE(ra _ rb _ rc);
  TRACE(prog);

  llint a_lo = 1, a_hi = 1;

  for (int i = 0; i < (int)prog.size() - 1; ++i) {
    a_lo *= 8LL;
    a_lo += 1LL;
    a_hi *= 8LL;
    a_hi += 1LL;
  }

  --a_lo;
  a_hi *= 8;

  TRACE(a_lo _ a_hi);
  assert((a_hi - a_lo) % 8 == 0);

  for (int i = 0; i < (int)prog.size(); ++i) {
    assert((a_hi - a_lo) % 8 == 0);
    llint offset = (a_hi - a_lo) / 8;
    for (int j = 0; j < 8; ++j) {
      llint a_cand = a_lo + j * offset;
      run_prog(a_cand);
      TRACE(out_buff);
      if (out_buff[(int) prog.size() - i - 1] == prog[(int) prog.size() - i - 1]) {
        a_lo = a_cand;
        a_hi = a_lo + offset;
        break;
      }
    }
    TRACE(a_lo _ a_hi);
  }

  for (llint i = a_lo - 1000000LL; i < a_lo + 1000000LL; ++i) {
    run_prog(i);
    if (out_buff == prog) {
      printf("%lld\n", i);
      break;
    }
  }

  return 0;
}
