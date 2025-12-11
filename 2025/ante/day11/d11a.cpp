#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

map<string, vector<string>> outs;
map<string, llint> C;

llint count(const string &node) {
  if (C.count(node)) 
    return C[node];
  if (node == "out")
    return 1;
  llint total = 0;
  for (auto &to : outs[node]) {
    total += count(to);
  }
  return C[node] = total;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string from;
    ss >> from;
    from.pop_back();
    string to;
    while (ss >> to) {
      outs[from].push_back(to);
    }
  }
  cout << count("you") << endl;
  return 0;
}
