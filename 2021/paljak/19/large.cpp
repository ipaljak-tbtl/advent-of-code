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
  int f = 1; o << "[";
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
const int MAXN = 110;

struct Point {
  int x, y, z;

  Point() {}
  Point(int x, int y, int z) : x(x), y(y), z(z) {}

  friend ostream& operator<<(ostream &os, const Point &dt) {
    os << "(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
  }

  friend bool operator < (const Point &A, const Point &B) {
    if (A.x != B.x) return A.x < B.x;
    if (A.y != B.y) return A.y < B.y;
    return A.z < B.z;
  }
};

const int dir[24][3][3] = {
  {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},
  {{1, 0, 0}, {0, 0, 1}, {0, -1, 0}},
  {{0, 1, 0}, {1, 0, 0}, {0, 0, -1}},
  {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}},
  {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}},
  {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}},
  {{1, 0, 0}, {0, -1, 0}, {0, 0, -1}},
  {{1, 0, 0}, {0, 0, -1}, {0, 1, 0}},
  {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}},
  {{0, 1, 0}, {0, 0, -1}, {-1, 0, 0}},
  {{0, 0, 1}, {-1, 0, 0}, {0, -1, 0}},
  {{0, 0, 1}, {0, -1, 0}, {1, 0, 0}},
  {{-1, 0, 0}, {0, 1, 0}, {0, 0, -1}},
  {{-1, 0, 0}, {0, 0, 1}, {0, 1, 0}},
  {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}},
  {{0, -1, 0}, {0, 0, 1}, {-1, 0, 0}},
  {{0, 0, -1}, {1, 0, 0}, {0, -1, 0}},
  {{0, 0, -1}, {0, 1, 0}, {1, 0, 0}},
  {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}},
  {{-1, 0, 0}, {0, 0, -1}, {0, -1, 0}},
  {{0, -1, 0}, {-1, 0, 0}, {0, 0, -1}},
  {{0, -1, 0}, {0, 0, -1}, {1, 0, 0}},
  {{0, 0, -1}, {-1, 0, 0}, {0, 1, 0}},
  {{0, 0, -1}, {0, -1, 0}, {-1, 0, 0}},
};

int n;

vector<Point> scanner[MAXN];
Point scanners[MAXN];
set<int> matched, unmatched;

vector<Point> read_points() {
  vector<Point> ret;
  int x, y, z;
  while (scanf("%d,%d,%d\n", &x, &y, &z) == 3)
    ret.emplace_back(x, y, z);
  return ret;
}

inline void read_input() {
  char dummy;
  scanf("%c", &dummy);
  while (scanf("-- scanner %d ---\n", &n) == 1)
    scanner[n] = read_points();
  ++n;
}

inline void init() {
  scanners[0] = Point(0, 0, 0);
  matched.insert(0);
  for (int i = 1; i < n; ++i) unmatched.insert(i);
}

bool match(int a, int b) {
  set<Point> fixed;
  for (auto &p : scanner[a])
    fixed.insert(p);

  for (int i = 0; i < 24; ++i) {
    vector<Point> curr;
    int cnt = 0;
    for (auto &p : scanner[b]) {
      curr.emplace_back(
          p.x * dir[i][0][0] + p.y * dir[i][1][0] + p.z * dir[i][2][0],
          p.x * dir[i][0][1] + p.y * dir[i][1][1] + p.z * dir[i][2][1],
          p.x * dir[i][0][2] + p.y * dir[i][1][2] + p.z * dir[i][2][2]
      );
    }
    for (auto &pa : fixed) {
      for (auto &pb : curr) {
        Point vec(pb.x - pa.x, pb.y - pa.y, pb.z - pa.z);
        int cnt = 0;
        for (auto &pp : curr)
          cnt += fixed.find(Point(pp.x - vec.x, pp.y - vec.y, pp.z - vec.z)) !=
                 fixed.end();
        if (cnt < 12) continue;
        scanner[b] = curr;
        scanners[b] = vec;
        for (auto &p : scanner[b])
          p = Point(p.x - vec.x, p.y - vec.y, p.z - vec.z);
        unmatched.erase(b);
        matched.insert(b);
        TRACE("MATCHED" _ a _ b _ cnt);
        return true;
      }
    }
  }

  return false;
}

int main(void) {
  read_input();
  init();

  while (!unmatched.empty()) {
    for (int i : matched)
      for (int j : unmatched)
        if (match(i, j)) goto escape;
    assert(false);
    escape:;
  }

  set<Point> beacons;
  for (int i = 0; i < n; ++i)
    for (auto &p : scanner[i])
      beacons.insert(p);

  int sol = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      auto p1 = scanners[i], p2 = scanners[j];
      sol = max(sol, abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z));
    }
  }

  printf("%d\n", sol);
  return 0;
}
