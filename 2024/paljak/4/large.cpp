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

const int MAXN = 150;

const int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int ds[] = {0, 1, 1, 1, 0, -1, -1, -1};

const char *target = "MAS";

int n;
char grid[MAXN][MAXN];

inline bool inside(int r, int s) { return r >= 0 && r < n && s >= 0 && s < n; }

bool check_word(int r, int s, int k) {
  for (int i = 0; i < strlen(target); ++i)
    if (!inside(r + i * dr[k], s + i * ds[k]) ||
        grid[r + i * dr[k]][s + i * ds[k]] != target[i])
      return false;
  return true;
}

int main(void) {
  while (scanf("%s", grid[n++]) == 1)
    ;
  --n;

  int sol = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (grid[i][j] == 'A')
        sol += (check_word(i - 1, j - 1, 3) || check_word(i + 1, j + 1, 7)) *
               (check_word(i - 1, j + 1, 5) || check_word(i + 1, j - 1, 1));

  printf("%d\n", sol);

  return 0;
}
