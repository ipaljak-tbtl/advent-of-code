#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

int n;
vector<llint> lo;
vector<llint> hi;


llint ktimes(llint x, int k) {
    string s = to_string(x);
    if (s.size()*k > 10)
        return LLONG_MAX;
    for (int i=0; i<k-1; i++)
        s += to_string(x);
    return stoll(s);
}

bool inside(llint x) {
  for (int i=0; i<(int)lo.size(); i++) {
    if (lo[i] <= x && x <= hi[i])
      return true;
  }
  return false;
}

int main() {
  llint largest = -1;
  do {
    llint x, y;
    scanf("%lld-%lld", &x, &y);
    lo.push_back(x);
    hi.push_back(y);
    largest = max(largest, y);
    TRACE(x _ y);
  } while (getchar() != '\n');

  llint sum = 0;
  set<llint> done;
  for (int k=2; k<=10; k++)
    for (llint i=1; ; i++) {
      llint ii = ktimes(i, k);
      if (ii > largest) 
        break;
      if (inside(ii) && done.count(ii) == 0) {
        done.insert(ii);
        sum += ii;
      }
    }

  cout << sum << endl;

  return 0;
}
