#include <bits/stdc++.h>

using namespace std;

string in[10];;

bool subset(const string &a, const string &b) {
  set<char> ss;
  for (char c : b) ss.insert(c);
  for (char c : a)
    if (ss.find(c) == ss.end())
      return false;
  return true;
}

int diff(const string &a, const string &b) {
  set<char> ss;
  for (char c : b) ss.insert(c);
  int ret = 0;
  for (char c : a)
    ret += ss.find(c) == ss.end();
  return ret;
}

int main(void) {
  int sol = 0;
  while (cin >> in[0]) {
    string match[10];
    for (int i = 1; i < 10; ++i)
      cin >> in[i];

    // 1, 4, 7, 8
    for (int i = 0; i < 10; ++i) {
      if (in[i].size() == 2) match[1] = in[i];
      if (in[i].size() == 3) match[7] = in[i];
      if (in[i].size() == 4) match[4] = in[i];
      if (in[i].size() == 7) match[8] = in[i];
    }

    // 2, 5, 3
    for (int i = 0; i < 10; ++i) {
      if (in[i].size() != 5) continue;
      if (subset(match[7], in[i])) {
          match[3] = in[i];
          continue;
      }
      if (diff(match[4], in[i]) == 1)
        match[5] = in[i];
      else
        match[2] = in[i];
    }

    // 0. 6, 9
    for (int i = 0; i < 10; ++i) {
      if (in[i].size() != 6) continue;
      if (!subset(match[5], in[i])) {
          match[0] = in[i];
          continue;
      }
      if (subset(match[7], in[i]))
        match[9] = in[i];
      else
        match[6] = in[i];
    }

    map<string, int> rev_match;
    for (int i = 0; i < 10; ++i) {
      sort(match[i].begin(), match[i].end());
      rev_match[match[i]] = i;
    }


    string s;
    cin >> s;
    int curr = 0;
    for (int i = 0; i < 4; ++i) {
      cin >> s;
      sort(s.begin(), s.end());
      curr *= 10;
      curr += rev_match[s];
    }

    sol += curr;
  }

  cout << sol << endl;
  return 0;
}
