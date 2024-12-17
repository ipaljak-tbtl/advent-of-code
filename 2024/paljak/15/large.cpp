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

const int MAXN = 110;
const int MAXL = 1010;

const map<char, pair<int, int>> DIR = {
    {'^', {-1, 0}}, {'v', {1, 0}}, {'<', {0, -1}}, {'>', {0, 1}}};

char grid[MAXN][MAXN];
char line[MAXN], moves[MAXL];

int r, s, robot_r, robot_s;

inline void print() {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j)
      printf("%c", grid[i][j]);
    printf("\n");
  }
  printf("\n");
  printf("\n");
}

void horizontal_move(char dir) {
  int rr = robot_r + DIR.at(dir).first;
  int ss = robot_s + DIR.at(dir).second;

  while (grid[rr][ss] == '[' or grid[rr][ss] == ']')
    rr += DIR.at(dir).first, ss += DIR.at(dir).second;

  if (grid[rr][ss] == '#')
    return;

  while (true) {
    swap(grid[rr][ss], grid[rr - DIR.at(dir).first][ss - DIR.at(dir).second]);
    if (grid[rr][ss] == '@')
      break;
    rr -= DIR.at(dir).first;
    ss -= DIR.at(dir).second;
  }

  robot_r = rr, robot_s = ss;
}

bool try_vertical_move(int curr_r, int curr_s, char dir,
                       set<pair<int, int>> &pts) {
  if (grid[curr_r][curr_s] == '#')
    return false;

  if (grid[curr_r][curr_s] == '.')
    return true;

  pts.insert({curr_r, curr_s});

  int rr = curr_r + DIR.at(dir).first;
  int ss = curr_s + DIR.at(dir).second;

  if (grid[curr_r][curr_s] == '@')
    return try_vertical_move(rr, ss, dir, pts);

  if (grid[curr_r][curr_s] == '[') {
    pts.insert({curr_r, curr_s + 1});
    return try_vertical_move(rr, ss, dir, pts) &&
           try_vertical_move(rr, ss + 1, dir, pts);
  }

  if (grid[curr_r][curr_s] == ']') {
    pts.insert({curr_r, curr_s - 1});
    return try_vertical_move(rr, ss, dir, pts) &&
           try_vertical_move(rr, ss - 1, dir, pts);
  }

  assert(false);
}

void vertical_move(char dir) {
  set<pair<int, int>> pts_set;

  if (!try_vertical_move(robot_r, robot_s, dir, pts_set))
    return;

  vector<pair<int, int>> pts(pts_set.begin(), pts_set.end());
  sort(pts.begin(), pts.end());
  if (dir == 'v')
    reverse(pts.begin(), pts.end());

  for (const auto &p : pts) {
    int rr = p.first + DIR.at(dir).first;
    int ss = p.second + DIR.at(dir).second;
    swap(grid[rr][ss], grid[p.first][p.second]);
  }

  robot_r = robot_r + DIR.at(dir).first;
  robot_s = robot_s + DIR.at(dir).second;
}

void move_robot(char dir) {
  assert(grid[robot_r][robot_s] == '@');

  if (dir == '>' || dir == '<')
    horizontal_move(dir);
  else
    vertical_move(dir);
}

void move_robot(const char *moves) {
  int n = strlen(moves);
  for (int i = 0; i < n; ++i)
    move_robot(moves[i]);
}

int main(void) {
  while (scanf("%s", line)) {
    for (int i = 0; i < strlen(line); ++i) {
      if (line[i] == '#')
        grid[r][2 * i] = grid[r][2 * i + 1] = '#';
      if (line[i] == '.')
        grid[r][2 * i] = grid[r][2 * i + 1] = '.';
      if (line[i] == 'O')
        grid[r][2 * i] = '[', grid[r][2 * i + 1] = ']';
      if (line[i] == '@')
        grid[r][2 * i] = '@', grid[r][2 * i + 1] = '.';
    }

    if (r == 0) {
      s = strlen(grid[r]);
      ++r;
      continue;
    }

    ++r;
    bool last = true;
    for (int i = 0; i < s; ++i)
      last &= grid[r - 1][i] == '#';
    if (last)
      break;
  }

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] == '@')
        robot_r = i, robot_s = j;

  print();

  while (scanf("%s", moves) == 1)
    move_robot(moves);

  print();

  int sol = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (grid[i][j] == '[')
        sol += 100 * i + j;

  printf("%d\n", sol);

  return 0;
}
