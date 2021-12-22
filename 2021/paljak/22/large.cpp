#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

struct Cube {
  int x1, x2, y1, y2, z1, z2;

  Cube () {}
  Cube (int x1, int x2, int y1, int y2, int z1, int z2) : x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2) {}

  friend bool operator < (const Cube &A, const Cube &B) {
    if (A.x1 != B.x1) return A.x1 < B.x1;
    if (A.x2 != B.x2) return A.x2 < B.x2;
    if (A.y1 != B.y1) return A.y1 < B.y1;
    if (A.y2 != B.y2) return A.y2 < B.y2;
    if (A.z1 != B.z1) return A.z1 < B.z1;
    return A.z2 < B.z2;
  }
};

map<Cube, int> cubes;

int main(void) {
  char s[5];
  int x1, x2, y1, y2, z1, z2;
  while (scanf("%s x=%d..%d,y=%d..%d,z=%d..%d", s, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    if (z1 > z2) swap(z1, z2);

    Cube curr(x1, x2, y1, y2, z1, z2);

    auto n_cubes = cubes;

    for (const auto &C : cubes) {
      int int_x1 = max(curr.x1, C.first.x1), int_x2 = min(curr.x2, C.first.x2);
      int int_y1 = max(curr.y1, C.first.y1), int_y2 = min(curr.y2, C.first.y2);
      int int_z1 = max(curr.z1, C.first.z1), int_z2 = min(curr.z2, C.first.z2);
      if (int_x1 > int_x2 || int_y1 > int_y2 || int_z1 > int_z2) continue;
      n_cubes[Cube(int_x1, int_x2, int_y1, int_y2, int_z1, int_z2)] -= C.second;
    }

    n_cubes[curr] += s[1] == 'n';
    cubes = n_cubes;
  }

  llint sol = 0;
  for (const auto &C : cubes)
    sol += (llint) C.second * (C.first.x2 - C.first.x1 + 1) *
                              (C.first.y2 - C.first.y1 + 1) *
                              (C.first.z2 - C.first.z1 + 1);

  printf("%lld\n", sol);
  return 0;
}
