#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

vector<int> read_csv() {
  string line;
  vector<int> result;
  if (!(cin >> line))
    return result;
  istringstream in(line);
  int value = 0;
  while (in >> value) {
    result.push_back(value);
    char c;
    in >> c;
    assert(c == ',');
  }
  return result;
}

int main() {
  vector<int> numbers = read_csv();
  vector<int> state(9, 0);
  for (auto &x : numbers)
    state[x]++;
  for (int i=0, s=0; i<80; i++, s=(s+1)%9)
    state[(s+7)%9] += state[s];
  int sum = 0;
  for (auto &x : state)
    sum += x;
  cout << sum << endl;
  return 0;
}
