#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;


vector<int> expand(string s) {
  vector<int> res;
  for (int i = 0; i < (int)s.size(); i++)
    if (i%2 == 0) {
      vector<int> tmp(s[i] - '0', i/2);
      res.insert(res.end(), tmp.begin(), tmp.end());
    } else {
      vector<int> tmp(s[i] - '0', -1);
      res.insert(res.end(), tmp.begin(), tmp.end());
    }
  return res;
}


vector<int> compact(const vector<int> &v) {
  int left = 0;
  int right = (int)v.size()-1;
  vector<int> res = v;
  while (left < right) {
    while (left < right && res[right] == -1) right--;
    while (left < right && res[left] != -1) left++;
    if (left < right) {
      res[left] = res[right];
      res[right] = -1;
      left++;
      right--;
    }
  }
  return res;
}


llint checksum(const vector<int> &v) {
  llint sum = 0;
  for (int i = 0; i < (int)v.size(); i++)
    if (v[i] != -1)
    sum += v[i] * i;
  return sum;
}


int main() {
  string s;
  cin >> s;
  auto exp = expand(s);
  auto com = compact(exp);
  cout << checksum(com) << endl;
  return 0;
}
