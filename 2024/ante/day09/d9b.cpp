#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


typedef long long llint;


int find_first(const vector<int> &v, int len) {
  int cnt = 0;
  for (int i = 0; i <(int)v.size(); i++) {
    if (v[i] == -1) {
      cnt++;
      if (cnt >= len)
        return i-len+1;
    } else
      cnt = 0;
  }
  return -1;
}

vector<int> expand_and_compact(string s) {
  vector<int> block;
  int n = 0;
  vector<int> size;
  vector<int> start;
  for (int i = 0; i < (int)s.size(); i++)
    if (i%2 == 0) {
      vector<int> tmp(s[i] - '0', i/2);
      start.push_back(block.size());
      size.push_back(tmp.size());
      block.insert(block.end(), tmp.begin(), tmp.end());
      n++;
    } else {
      vector<int> tmp(s[i] - '0', -1);
      block.insert(block.end(), tmp.begin(), tmp.end());
    }

  for (int i = n-1; i >= 0; i--) {
    int pos = find_first(block, size[i]);
    if (pos == -1 || pos >= start[i])
      continue;
    for (int j=0; j <size[i]; j++) {
      block[pos+j] = block[start[i]+j];
      block[start[i]+j] = -1;
    }
  }

  return block;
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
  auto com = expand_and_compact(s);
  cout << checksum(com) << endl;
  return 0;
}
