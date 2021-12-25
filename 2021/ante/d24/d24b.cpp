#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef array<int, 4> Q;

const Q ERROR = {1<<30, 1<<30, 1<<30, 1<<30};

int n;
vector<char> cmd;
vector<int> arg1;
vector<int> arg2;
vector<int> imm2;

void read_input() {
  char s[1024];
  char c;
  int cnti = 0;
  while (scanf( "%s %c", s, &c) == 2) {
    if (s[1] == 'o')
      s[0] = 'o';
    cmd.push_back(s[0]);
    assert(c == 'w' || c == 'x' || c == 'y' || c == 'z');
    arg1.push_back(c - 'w');
    if (s[0] == 'i') {
      arg2.push_back(-1);
      imm2.push_back(cnti);
      cnti++;
      continue ;
    }
    assert(scanf(" %c", &c) == 1);
    if (isdigit(c) || c == '-') {
      ungetc(c, stdin);
      int x;
      assert(scanf("%d", &x) == 1);
      arg2.push_back(-1);
      imm2.push_back(x);
      continue ;
    }
    assert(c == 'w' || c == 'x' || c == 'y' || c == 'z');    
    arg2.push_back(c-'w');
    imm2.push_back(-1);
  }
  n = cmd.size();
}

inline Q step(const Q &state, int k) {
  Q s = state;
  if (cmd[k] == 'i') {
    s[arg1[k]] = imm2[k];
    return s;
  }
  if (cmd[k] == 'a' && arg2[k] != -1) {
    s[arg1[k]] += s[arg2[k]];
    return s;
  }
  if (cmd[k] == 'a' && arg2[k] == -1) {
    s[arg1[k]] += imm2[k];
    return s;
  }
  if (cmd[k] == 'm' && arg2[k] != -1) {
    s[arg1[k]] *= s[arg2[k]];
    return s;
  }
  if (cmd[k] == 'm' && arg2[k] == -1) {
    s[arg1[k]] *= imm2[k];
    return s;
  }  
  if (cmd[k] == 'd' && arg2[k] != -1) {
    if (s[arg2[k]] == 0)
      return ERROR;
    s[arg1[k]] /= s[arg2[k]];
    return s;
  }
  if (cmd[k] == 'd' && arg2[k] == -1) {
    if (imm2[k] == 0)
      return ERROR;
    s[arg1[k]] /= imm2[k];
    return s;
  } 
  if (cmd[k] == 'o' && arg2[k] != -1) {
    if (s[arg2[k]] == 0 || s[arg1[k]] < 0)
      return ERROR;
    s[arg1[k]] %= s[arg2[k]];
    return s;
  }
  if (cmd[k] == 'o' && arg2[k] == -1) {
    if (imm2[k] == 0 || s[arg1[k]] < 0)
      return ERROR;
    s[arg1[k]] %= imm2[k];
    return s;
  }
  if (cmd[k] == 'e' && arg2[k] != -1) {
    s[arg1[k]] = s[arg1[k]] == s[arg2[k]];
    return s;
  }
  if (cmd[k] == 'e' && arg2[k] == -1) {
    s[arg1[k]] = s[arg1[k]] == imm2[k];
    return s;
  }
  assert(false);
}

int possible(const vector<int> input) {
  assert(input.size() == 14);
  set<Q> states;
  states.insert({0, 0, 0, 0});  
  return !states.empty();
}    

vector<set<Q>> D;

void search(int k, Q state) {
  while (k < n && cmd[k] != 'i') {
    state = step(state, k);
    if (state == ERROR)
      return ;
    k++;
  }     

  if (k == n && !state.at(3)) {
    for (int i=0; i<n; i++)
      if (cmd[i] == 'i')
        cout << imm2[i];
    cout << endl;
    exit(0);
  }
  
  if (k == n)
    return ;
  
  if (D[k].count(state))
    return ;

  D[k].insert(state);
  for (imm2[k]=1; imm2[k]<10; imm2[k]++) {
    Q next = step(state, k);
    if (state == ERROR)
      continue ;
    search(k+1, next);
  }    
}

int main() {
  read_input();
  D.resize(n);
  search(0, {0, 0, 0, 0});
  cout << "No solution" << endl;
  return 0;
}
