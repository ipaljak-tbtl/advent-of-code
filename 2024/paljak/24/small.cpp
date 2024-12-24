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

struct Input {
  string in1, in2, oper;
  Input() {}
  Input(string in1, string in2, string oper) : in1(in1), in2(in2), oper(oper) {}
};

map<string, Input> m;
map<string, bool> val;

bool get_val(string node) {
  if (val.find(node) != val.end())
    return val[node];

  Input in = m[node];
  bool in1 = get_val(in.in1), in2 = get_val(in.in2);

  if (in.oper == "AND")
    return val[node] = in1 & in2;

  if (in.oper == "OR")
    return val[node] = in1 | in2;

  if (in.oper == "XOR")
    return val[node] = in1 ^ in2;

  assert(false);
}

int main(void) {
  string node;
  bool v;
  while (cin >> node) {
    if (*node.rbegin() != ':')
      break;
    cin >> v;
    node.pop_back();
    val[node] = v;
  }

  TRACE(val);

  string a = node, b, c, op, dummy;
  cin >> op >> b >> dummy >> c;
  do {
    TRACE(a _ op _ b _ dummy _ c);
    m[c] = Input(a, b, op);
  } while (cin >> a >> op >> b >> dummy >> c);

  llint sol = 0;
  for (int bit = 0; bit < 63; ++bit) {
    stringstream ss;
    ss << 'z' << setw(2) << setfill('0') << bit;
    string node = ss.str();
    TRACE(node);
    if (m.find(node) == m.end())
      break;
    sol |= ((llint)get_val(node)) << bit;
  }

  printf("%lld\n", sol);

  return 0;
}
