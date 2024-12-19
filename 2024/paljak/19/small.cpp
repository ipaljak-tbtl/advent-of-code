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

vector<string> pattern;

bool check(const string &query) {
  vector<bool> dp(query.length() + 1, false);
  dp[0] = true;
  for (int i = 1; i <= (int)query.length(); ++i) {
    for (auto &p : pattern) {
      if (i - p.length() < 0)
        continue;
      bool ok = true;
      for (int j = i - p.length(); j < i; ++j)
        ok &= p[j - i + p.length()] == query[j];
      if (ok)
        dp[i] = dp[i] | dp[i - p.length()];
    }
  }
  return dp[query.length()];
}

int main(void) {
  string token;
  while (true) {
    cin >> token;
    if (*token.rbegin() == ',') {
      token.pop_back();
      pattern.push_back(token);
    } else {
      pattern.push_back(token);
      break;
    }
  }

  string query;
  int sol = 0;
  while (cin >> query)
    sol += check(query);

  cout << sol << endl;
  return 0;
}
