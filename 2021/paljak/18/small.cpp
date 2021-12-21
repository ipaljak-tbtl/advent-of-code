#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<

template <class> struct is_container : false_type {};
template <class... Ts> struct is_container<vector<Ts...>> : true_type {};
template <class... Ts> struct is_container<map<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template <class... Ts> struct is_container<list<Ts...>> : true_type {};
template <class... Ts> struct is_container<set<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template <class T, class = typename enable_if<is_container<T>::value>::type>
ostream& operator << (ostream &o, T x) {
  int f = 1;
  o << "[";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "]";
}
template<class T, class U>
ostream& operator<< (ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}

typedef long long llint;

const int MOD = 1e9 + 7;

int ceil(int a, int b) {
  return (a + b - 1) / b;
}

struct Tree {
  // lvl, val
  vector<pair<int, int>> leaves;

  Tree() {}
  Tree(vector<pair<int, int>> leaves) : leaves(leaves) {}

  void reduce() {
    for (int i = 0; i < (int) leaves.size() - 1; ++i) {
      if (leaves[i].first <= 4) continue;
      assert(leaves[i + 1].first == leaves[i].first);
      if (i > 0) leaves[i - 1].second += leaves[i].second;
      if (i + 2 < leaves.size()) leaves[i + 2].second += leaves[i + 1].second;
      leaves[i].first--;
      leaves[i].second = 0;
      leaves.erase(leaves.begin() + i + 1);
      reduce();
      return;
    }
    for (int i = 0; i < (int) leaves.size(); ++i) {
      if (leaves[i].second < 10) continue;
      int l = leaves[i].second / 2, r = ceil(leaves[i].second, 2);
      leaves[i].first++;
      leaves[i].second = l;
      leaves.push_back(*leaves.rbegin());
      for (int j = leaves.size() - 1; j > i; --j)
        leaves[j] = leaves[j - 1];
      leaves[i + 1].second = r;
      assert(leaves[i].first == leaves[i + 1].first);
      reduce();
      return;
    }
  }

  int magnitude() {
    vector<pair<int, int>> l_copy = leaves;
    while (l_copy.size() > 1) {
      for (auto it = l_copy.begin(); it != prev(l_copy.end()); ++it) {
        auto nxt = next(it);
        if (it->first == nxt->first) {
          it->second *= 3; it->second += 2 * nxt->second;
          it->first--;
          l_copy.erase(nxt);
          break;
        }
      }
    }
    return l_copy.begin()->second;
  }
};

Tree operator + (const Tree &L, const Tree &R) {
  vector<pair<int, int>> leaves;
  for (auto &p : L.leaves) leaves.emplace_back(p.first + 1, p.second);
  for (auto &p : R.leaves) leaves.emplace_back(p.first + 1, p.second);
  Tree ret(leaves);
  ret.reduce();
  return ret;
}

vector<Tree> in;

vector<pair<int, int>> parse_tree(const string &s) {
  int lvl = 0, val = -1;
  vector<pair<int, int>> ret;
  for (auto c : s) {
    if (!(c >= '0' && c <= '9') && val != -1) {
      ret.emplace_back(lvl, val);
      val = -1;
    }
    if (c == ',') continue;
    if (c == '[') { ++lvl; continue; }
    if (c == ']') { --lvl; continue; }
    if (val == -1) val = 0;
    val *= 10; val += c - '0';
  }
  return ret;
}

int main(void) {
  string l;
  while (cin >> l)
    in.emplace_back(parse_tree(l));

  Tree ret = in[0];
  for (int i = 1; i < in.size(); ++i)
    ret = ret + in[i];

  cout << ret.magnitude() << endl;

  return 0;
}
