#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

void step(const map<string, char> &rules, map<string, long long> &freq) {
  map<string, long long> newfreq;
  for (auto [s, x] : freq)
    if (rules.count(s)) {
      string s1 = string() + s[0] + rules.at(s);
      string s2 = string() + rules.at(s) + s[1];
      newfreq[s1] += x;
      newfreq[s2] += x;
    } else {
      newfreq[s] += x;
    }
  swap(freq, newfreq);
}

vector<long long> count(const map<string, long long> freq) {
  vector<long long> cnt(26, 0);
  for (auto [s, x] : freq) {
    if (s[0] != '$')
      cnt[s[0]-'A'] += x;
    if (s[1] != '$')
      cnt[s[1]-'A'] += x;
  }
  for (auto &c : cnt)
    c /= 2;
  return cnt;
}

int main() {
  map<string, long long> freq;
  string s;
  cin >> s;
  s = "$" + s + "$";
  for (int i=0; i<(int)s.size()-1; i++)
    freq[s.substr(i, 2)]++;
  
  map<string, char> rules;
  string a, b, c;
  while (cin >> a >> b >> c) {
    assert(b == "->");
    rules[a] = c[0];
  }
  
  for (int i=0; i<40; i++)
    step(rules, freq);

  auto cnt = count(freq);
  long long lo = -1;
  long long hi = -1;
  for (auto c : cnt) {
    if (c == 0)
      continue ;
    if (lo == -1 || c < lo)
      lo = c;
    if (hi == -1 || c > hi)
      hi = c;
  }

  cout << hi-lo << endl;
  
  return 0;
}
