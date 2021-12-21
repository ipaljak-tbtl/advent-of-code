#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

struct point {
  int x;
  int y;
  int z;
};

ostream& operator<< (ostream &o, const point &a) {
  return o << "(" << a.x << ", " << a.y << ", " << a.z << ")";
}

bool operator< (const point &a, const point &b) {
  return make_pair(a.x, make_pair(a.y, a.z)) < make_pair(b.x, make_pair(b.y, b.z));
}

bool operator== (const point &a, const point &b) {
  return make_pair(a.x, make_pair(a.y, a.z)) == make_pair(b.x, make_pair(b.y, b.z));
}

point operator+ (const point &a, const point &b) {
  return point{a.x+b.x, a.y+b.y, a.z+b.z};
}

point operator- (const point &a, const point &b) {
  return point{a.x-b.x, a.y-b.y, a.z-b.z};
}

point operator- (const point &a) {
  return point{-a.x, -a.y, -a.z};
}

int operator* (const point &a, const point &b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

point cross (const point &a, const point &b) {
  return point{a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}

point rotate(const point &a, const point &X, const point &Y, const point &Z) {
  return point{X*a, Y*a, Z*a};
}

const vector<point> AXES = {
  point{1, 0, 0},
  point{-1, 0, 0},
  point{0, 1, 0},
  point{0, -1, 0},
  point{0, 0, 1},
  point{0, 0, -1}
};

typedef vector<point> points;

vector<points> scanners;

int try_merge(int a, int b) {
  set<point> sa(scanners[a].begin(), scanners[a].end());
  for (point X: AXES)
    for (point Y : AXES)
      if (X*Y == 0) {
        point Z = cross(X, Y);
        points rb = scanners[b];
        for (auto &p : rb)
          p = rotate(p, X, Y, Z);
        for (auto oa : scanners[a])
          for (auto ob : rb) {
            point delta = ob-oa;
            points trb = rb;
            int count = 0;
            for (auto &q : trb) {
              q = q-delta;
              count += sa.count(q);
            }
            if (count >= 12) {
              scanners[b] = trb;
              return 1;
            }
          }
      }
  return 0;
}

void merge() {
  int n = scanners.size();
  vector<int> done(n, 0);
  queue<int> q;
  done[0] = 1;
  q.push(0);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int j=0; j<n; j++)
      if (!done[j] && try_merge(x, j)) {
        done[j] = 1;
        q.push(j);
      }
  }
  
  for (int i=0; i<n; i++)
    assert(done[i]);
}

int count() {
  set<point> A;
  for (auto s : scanners)
    for (auto p : s)
      A.insert(p);
  return A.size();
}

int main() {
  int tmp = 0;
  int step = 0;
  while (scanf(" --- scanner %d --- ", &tmp) == 1) {
    assert(tmp == step);
    step++;
    point p{0, 0, 0};
    points current;
    while (scanf(" %d,%d,%d\n", &p.x, &p.y, &p.z) == 3)
      current.push_back(p);
    scanners.push_back(current);
    ungetc('-', stdin);
  }
  merge();
  cout << count() << endl;
  return 0;
}
