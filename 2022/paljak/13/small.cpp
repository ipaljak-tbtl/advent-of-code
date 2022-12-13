#include <bits/stdc++.h>

using namespace std;

struct Element {
  bool is_int;
  int int_val;
  vector<Element> list_val;

  Element() {}
  Element(int val): is_int(true), int_val(val) {}

  void add(Element ch) {
    list_val.emplace_back(ch);
  }
};

bool operator < (const Element &lhs, const Element &rhs) {
  if (lhs.is_int && rhs.is_int) return lhs.int_val < rhs.int_val;

  if (!lhs.is_int && !rhs.is_int) {
    for (int i = 0; i < min(lhs.list_val.size(), rhs.list_val.size()); ++i) {
      if (lhs.list_val[i] < rhs.list_val[i]) return true;
      if (rhs.list_val[i] < lhs.list_val[i]) return false;
    }
    return lhs.list_val.size() < rhs.list_val.size();
  }

  Element tmp;
  tmp.is_int = false;
  if (lhs.is_int) {
    Element L;
    L.is_int = false;
    L.add(lhs);
    return L < rhs;
  }

  Element R;
  R.is_int = false;
  R.add(rhs);
  return lhs < R;
}

string s;
int match[250];

inline void precompute() {
  stack<int> st;
  for (int i = 0; i < (int) s.size(); ++i) {
    if (s[i] == '[') st.push(i);
    if (s[i] == ']') { match[st.top()] = i; st.pop(); }
  }
}

Element parse(int lo, int hi) {
  if (s[lo] != '[')
    return Element(stoi(s.substr(lo, hi - lo)));

  Element ret;
  ret.is_int = false;
  ++lo;

  while (lo < hi) {
    if (s[lo] == '[') {
      ret.add(parse(lo, match[lo]));
      lo = match[lo] + 2;
    } else {
      int nxt = lo + 1;
      while (nxt < hi && s[nxt] != ',') ++nxt;
      ret.add(Element(stoi(s.substr(lo, nxt - lo))));
      lo = nxt + 1;
    }
  }

  return ret;
}

int main(void) {
  vector<Element> v;
  while (cin >> s) {
    precompute();
    v.emplace_back(parse(0, (int)s.size() - 1));
  }

  int sol = 0;
  for (int i = 0; i < (int)v.size(); i += 2)
    sol += (v[i] < v[i + 1]) * (i / 2 + 1);

  cout << sol << endl;

  return 0;
}
