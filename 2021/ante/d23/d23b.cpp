#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

const int C[4] = {1, 10, 100, 1000};
typedef pair<int, int> P;
typedef vector<P> state;

int n;
state L;
map<state, int> Memo;

void read_input() {
  string line;
  cin >> line;
  n = ((int)line.size() - 5) / 2;
  cin >> line;
  assert(line == string() + "#" + string(2*n + 3, '.') + "#");
  L.resize(4*n);
  for (int j=0; j<4; j++) {
    cin >> line;
    if (j > 0)
      line = string() + "##" + line + "##";
    assert((int)line.size() == 2*n + 5);
    for (int i=0; i<n; i++) {
      int kind = line[2*i + 3] - 'A';
      int idx = 4*kind;
      while (L[idx] != P{0, 0})
        idx++;
      L[idx] = {2*i+3, j+1};
    }
  }
}

int is_done(const state &L) {
  for (int i=0; i<4*n; i++) 
    if (L[i].first != 2*(i/4) + 3)
      return 0;
  return 1;
}

int move_up(int a, int x, state &L) {
  auto [cx, cy] = L[a];
  int kind = a/4;
  int home = 2*kind+3;
  // already up
  if (cy == 0)
    return 0;
  // already done
  if (cx == home) {
    int need_to_move = 0;
    for (int i=0; i<4*n; i++)
      if (i/4 != kind && L[i].first == home && L[i].second > cy)
        need_to_move = 1;
    if (!need_to_move)
      return 0;
  }
  // something above
  if (cy > 1)
    for (auto [xx, yy] : L)
      if (xx == cx && yy < cy)
        return 0;
  // x not good
  if ((x-3)%2 == 0 && (x-3)/2 >= 0 && (x-3)/2 < n)
    return 0;
  // something blocking
  for (auto [xx, yy] : L)
    if (yy == 0 && xx >= min(x, cx) && xx <= max(x, cx))
      return 0;
  // we can move
  L[a] = {x, 0};
  return cy+abs(cx-x);
}

int move_down(int a, state &L) {
  auto [cx, cy] = L[a];
  int kind = a/4;
  int home = 2*kind+3;
  // already down
  if (cy != 0)
    return 0;
  // home not ready
  for (int i=0; i<4*n; i++) 
    if (L[i].first == home && i/4 != kind)
      return 0;
  // something blocking
  for (int i=0; i<4*n; i++)
    if (i != a) {
      auto [xx, yy] = L[i];
      if (yy == 0 && xx >= min(home, cx) && xx <= max(home, cx))
        return 0;
    }
  // we can move
  int y = 4;
  for (int i=kind*4; i<kind*4+4; i++)
    if (i != a && L[i].first == home) {
      y--;
    }
  L[a] = {home, y};
  return y+abs(cx-home);
}

  
int best(const state &L) {
  if (is_done(L))
    return 0;
  if (Memo.count(L))
    return Memo[L];
  
  int B = 1<<30;
  for (int i=0; i<4*n; i++)
    for (int k=1; k<=2*n+3; k++) {
      state nL = L;
      int steps = move_up(i, k, nL);
      if (steps == 0)
        continue ;
      B = min(B, C[i/4]*steps + best(nL));
    }
  
  for (int i=0; i<4*n; i++) {
    state nL = L;
    int steps = move_down(i, nL);
    if (steps == 0)
      continue ;
    B = min(B, C[i/4]*steps + best(nL));
  }
  
  return Memo[L] = B;
}

int main() {
  read_input();
  cout << best(L) << endl;
  return 0;
}
