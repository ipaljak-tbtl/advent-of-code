#include <algorithm>
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

const int L = 2;

const int DIR[] = {2, 1, 0, 3}; // ">v<^";
const int DR[] = {0, 1, 0, -1};
const int DS[] = {1, 0, -1, 0};

const llint INF = 1e18;

const string KEYPAD_BUTTONS = "<v>^A";
const string NUMPAD_BUTTONS = "0123456789A";

const vector<string> KEYPAD = {" ^A", "<v>"};
const vector<string> NUMPAD = {"789", "456", "123", " 0A"};

llint memo[6][6][L + 2];
llint dist[12][6];

inline void init() { memset(memo, -1, sizeof memo); }

inline pair<int, int> get_keypad_coord(const char c) {
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      if (KEYPAD[i][j] == c)
        return {i, j};
  assert(false);
}

inline pair<int, int> get_numpad_coord(const char c) {
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 3; ++j)
      if (NUMPAD[i][j] == c)
        return {i, j};
  assert(false);
}

llint dp(int s, int f, int l) {
  if (memo[s][f][l] != -1)
    return memo[s][f][l];

  if (l == 0)
    return memo[s][f][l] = 1LL;

  llint ret = 0;
  auto p = get_keypad_coord(KEYPAD_BUTTONS[s]);
  auto q = get_keypad_coord(KEYPAD_BUTTONS[f]);

  vector<int> nodes;

  if (p.first > q.first) {
    nodes.push_back(3);
    ret += (llint)(p.first - q.first - 1) * dp(3, 3, l - 1);
  }

  if (p.first < q.first) {
    nodes.push_back(1);
    ret += (llint)(q.first - p.first - 1) * dp(1, 1, l - 1);
  }

  if (p.second > q.second) {
    nodes.push_back(0);
    ret += (llint)(p.second - q.second - 1) * dp(0, 0, l - 1);
  }

  if (p.second < q.second) {
    nodes.push_back(2);
    ret += (llint)(q.second - p.second - 1) * dp(2, 2, l - 1);
  }

  if (nodes.empty()) {
    ret += dp(4, 4, l - 1);
    return memo[s][f][l] = ret;
  }

  sort(nodes.begin(), nodes.end());
  llint best = INF;

  do {
    if ((s == 4 || s == 3) && f == 0 && nodes[0] == 0)
      continue;
    if (s == 0 && (f == 4 || f == 3) && nodes[0] == 3)
      continue;
    llint curr = dp(4, nodes[0], l - 1);
    for (int i = 1; i < (int)nodes.size(); ++i)
      curr += dp(nodes[i - 1], nodes[i], l - 1);
    curr += dp(*nodes.rbegin(), 4, l - 1);
    best = min(best, curr);
  } while (next_permutation(nodes.begin(), nodes.end()));

  ret += best;
  return memo[s][f][l] = ret;
}

struct Node {
  int numpad_button, keypad_button;
  llint d;

  Node() {}
  Node(int numpad_button, int keypad_button, llint d)
      : numpad_button(numpad_button), keypad_button(keypad_button), d(d) {}

  friend bool operator<(const Node &A, const Node &B) { return A.d > B.d; }
};

inline bool inside(int rr, int ss) {
  return rr >= 0 && rr < 4 && ss >= 0 && ss < 3 && !(rr == 3 && ss == 0);
}

llint dijkstra(int s, int f) {
  priority_queue<Node> pq;
  memset(dist, -1, sizeof dist);

  pq.push(Node(s, 4, 0));
  while (!pq.empty()) {
    while (!pq.empty() &&
           dist[pq.top().numpad_button][pq.top().keypad_button] != -1)
      pq.pop();

    if (pq.empty())
      break;

    auto curr = pq.top();
    pq.pop();

    dist[curr.numpad_button][curr.keypad_button] = curr.d;

    const auto p = get_numpad_coord(NUMPAD_BUTTONS[curr.numpad_button]);
    for (int i = 0; i < 4; ++i) {
      int rr = p.first + DR[i], ss = p.second + DS[i];
      if (!inside(rr, ss))
        continue;
      char nxt_c = NUMPAD[rr][ss];
      int nc = nxt_c - '0';
      if (nxt_c == 'A')
        nc = 10;

      if (dist[nc][DIR[i]] != -1)
        continue;
      pq.push(Node(nc, DIR[i], curr.d + dp(curr.keypad_button, DIR[i], L)));
    }
  }

  llint ret = INF;
  for (int i = 0; i < 4; ++i)
    if (dist[f][DIR[i]] != -1)
      ret = min(ret, dist[f][DIR[i]] + dp(DIR[i], 4, L));

  return ret;
}

int main(void) {
  init();
  llint sol = 0;
  string code;
  while (cin >> code) {
    llint x = 0, y = 0;
    code = "A" + code;
    for (int i = 1; i < (int)code.size(); ++i) {
      int a = code[i - 1] - '0', b = code[i] - '0';
      if (code[i - 1] == 'A')
        a = 10;
      if (code[i] == 'A')
        b = 10;
      x += dijkstra(a, b);
      if (code[i] != 'A')
        y = y * 10 + b;
    }

    TRACE(code _ x _ y);
    sol += x * y;
  }

  printf("%lld\n", sol);
  return 0;
}
