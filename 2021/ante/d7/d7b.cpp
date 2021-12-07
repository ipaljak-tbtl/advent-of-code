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
  int best = -1;;
  int lo = *min_element(numbers.begin(), numbers.end());
  int hi = *max_element(numbers.begin(), numbers.end());
  for (int y=lo; y<=hi; y++) {
    int count = 0;
      for (auto &x: numbers)
        count += abs(x-y)*(abs(x-y)+1)/2;
    if (best == -1 || count < best)
      best = count;
  }
  cout << best << endl;
  return 0;
}
