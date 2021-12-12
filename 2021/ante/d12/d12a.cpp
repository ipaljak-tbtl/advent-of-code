#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

map<string, set<string>> edges;
map<string, int> done;

int count(string s) {
  if (s == "end")
    return 1;
  if (done[s])
    return 0;
  if (islower(s[0]))
    done[s] = 1;
  int cnt = 0;
  for (auto x : edges[s])
    cnt += count(x);
  done[s] = 0;
  return cnt;
}

int main() {
  string line;
  while (cin >> line) {
    char a[(int)line.size()+1];
    char b[(int)line.size()+1];
    assert(sscanf(line.c_str(), "%[a-zA-Z]-%[a-zA-Z]", a, b) == 2);
    string sa(a);
    string sb(b);
    edges[sa].insert(sb);
    edges[sb].insert(sa);
  }
  cout << count("start") << endl;
  return 0;
}
