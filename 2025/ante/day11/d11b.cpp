#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

map<string, vector<string>> outs;
map<string, llint> C;

llint count(string node, string end) {
  if (C.count(node)) 
    return C[node];
  if (node == end)
    return 1;
  llint total = 0;
  for (auto &to : outs[node]) {
    total += count(to, end);
  }
  return C[node] = total;
}

llint cnt(string start, string end) {
  C.clear();
  llint c = count(start, end);
  TRACE(start _ end _ c);
  return c;
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
  llint total = cnt("svr", "fft")*cnt("fft", "dac")*cnt("dac", "out");
  total += cnt("svr", "dac")*cnt("dac", "fft")*cnt("fft", "out");
  cout << total << endl;
  return 0;
}
