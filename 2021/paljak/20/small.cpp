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
const int MAXN = 1010;

int r, s;

char code[MAXN];
char grid[MAXN][MAXN];

char char_at(int i, int j) {
  if (i < 0 || j < 0 || i >= MAXN || j >= MAXN)
    return grid[0][0];
  return grid[i][j];
}

void step() {
  char _grid[MAXN][MAXN];
  for (int i = 0; i < MAXN; ++i) {
    for (int j = 0; j < MAXN; ++j) {
      int val = 0;
      for (int k = i - 1; k <= i + 1; ++k) {
        for (int l = j - 1; l <= j + 1; ++l) {
          val <<= 1;
          val += char_at(k, l) == '#';
        }
      }
      _grid[i][j] = code[val];
    }
  }

  for (int i = 0; i < MAXN; ++i)
    for (int j = 0; j < MAXN; ++j)
      grid[i][j] = _grid[i][j];
}

int main(void) {
  scanf("%s", code);

  memset(grid, '.', sizeof grid);

  char line[MAXN];
  while (scanf("%s", line) == 1) {
    ++r;
    s = strlen(line);
    for (int i = 0; i < s; ++i)
      grid[r + 500][i + 500] = line[i];
  }

  for (int i = 0; i < 2; ++i)
    step();

  int sol = 0;
  for (int i = 0; i < MAXN; ++i)
    for (int j = 0; j < MAXN; ++j)
      sol += grid[i][j] == '#';

  printf("%d\n", sol);

  return 0;
}
