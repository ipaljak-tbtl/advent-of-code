#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;

int n;
vector<llint> lo;
vector<llint> hi;


llint twice(llint x) {
    string s = to_string(x);
    return stoll(s+s);
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
  for (llint i=1; ; i++) {
    llint ii = twice(i);
    if (ii > largest) 
      break;
    if (inside(ii))
      sum += ii;
  }

  cout << sum << endl;

  return 0;
}
