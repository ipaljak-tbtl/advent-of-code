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
  sort(numbers.begin(), numbers.end());
  int count = 0;
  for (auto &x : numbers)
    count += abs(x-numbers[(int)numbers.size()/2]);
  cout << count << endl;
  return 0;
}
