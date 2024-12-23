#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


map<string, set<string>> L;


int main() {
  string line;
  while (cin >> line) {
    string a = string() + line[0] + line[1];
    string b = string() + line[3] + line[4];
    L[a].insert(b);
    L[b].insert(a);
  }

  vector<string> nodes;
  for (auto &[a, la] : L)
    nodes.push_back(a);

  TRACE(nodes.size());

  int total = 0;
  for (int i=0; i<(int)nodes.size(); i++)
    for (int j=i+1; j<(int)nodes.size(); j++)
      for (int k=j+1; k<(int)nodes.size(); k++)
        if (nodes[i][0] == 't' || nodes[j][0] == 't' || nodes[k][0] == 't')
          if (L[nodes[i]].count(nodes[j]) &&
              L[nodes[j]].count(nodes[k]) &&
              L[nodes[k]].count(nodes[i]))
            total++;

  cout << total << endl;
  return 0;
}
