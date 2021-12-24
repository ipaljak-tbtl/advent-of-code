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
  cin >> line;
  assert((int)line.size() == 2*n + 5);
  L.resize(2*n);
  for (int i=0; i<n; i++) {
    int kind = line[2*i + 3] - 'A';
    int idx = 2*kind;
    if (L[idx] != P{0, 0})
      idx++;
    L[idx] = {2*i+3, 1};
  }
  cin >> line;
  assert((int)line.size() == 2*n + 1);
  for (int i=0; i<n; i++) {
    int kind = line[2*i + 1] - 'A';
    int idx = 2*kind;
    if (L[idx] != P{0, 0})
      idx++;
    L[idx] = {2*i+3, 2};
  }
}

int is_done(const state &L) {
  for (int i=0; i<2*n; i++) 
    if (L[i].first != 2*(i/2) + 3)
      return 0;
  return 1;
}

int move_up(int a, int x, state &L) {
  auto [cx, cy] = L[a];
  int kind = a/2;
  int home = 2*kind+3;
  // already up
  if (cy == 0)
    return 0;
  // kind already done
  int c = a%2 == 0? a+1 : a-1;
  if (cx == home && L[c].first == home)
    return 0;
  // no need to move
  if (P{cx, cy} == P{home, 2})
    return 0;
  // something above
  if (cy == 2)
    for (auto [xx, yy] : L)
      if (P{xx, yy} == P{cx, 1})
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
  int kind = a/2;
  int home = 2*kind+3;
  // already down
  if (cy != 0)
    return 0;
  // home not ready
  for (int i=0; i<2*n; i++) 
    if (L[i].first == home && i/2 != kind)
      return 0;
  // something blocking
  for (int i=0; i<2*n; i++)
    if (i != a) {
      auto [xx, yy] = L[i];
      if (yy == 0 && xx >= min(home, cx) && xx <= max(home, cx))
        return 0;
    }
  // we can move
  int c = a%2 == 0? a+1 : a-1;
  int y = 2;
  if (L[c].first == home) {
    assert(L[c].second == 2);
    y = 1;
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
  for (int i=0; i<2*n; i++)
    for (int k=1; k<=2*n+3; k++) {
      state nL = L;
      int steps = move_up(i, k, nL);
      if (steps == 0)
        continue ;
      B = min(B, C[i/2]*steps + best(nL));
    }
  
  for (int i=0; i<2*n; i++) {
    state nL = L;
    int steps = move_down(i, nL);
    if (steps == 0)
      continue ;
    B = min(B, C[i/2]*steps + best(nL));
  }
  
  return Memo[L] = B;
}

int main() {
  read_input();
  cout << best(L) << endl;
  return 0;
}
