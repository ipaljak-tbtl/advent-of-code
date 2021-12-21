#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;


const int LPAREN = -1;
const int RPAREN = -2;

int explode(vector<int> &a) {
  for (int i=0, last_num=-1, level=0; i<(int)a.size(); i++) {
    if (a[i] >= 0)
      last_num = i;
    else if (a[i] == RPAREN)
      level--;
    else if (a[i] == LPAREN)
      level++;
    if (level < 5)
      continue ;
    if (last_num != -1)
      a[last_num] += a[i+1];
    for (int j=i+3; j<(int)a.size(); j++)
      if (a[j] >= 0) {
        a[j] += a[i+2];
        break ;
      }
    a[i] = 0;
    a.erase(a.begin()+i+1, a.begin()+i+4);
    return 1;
  }
  return 0;
}

int split(vector<int> &a) {
  for (int i=0; i<(int)a.size(); i++)
    if (a[i] >= 10) {
      int x = a[i];
      a[i] = RPAREN;
      a.insert(a.begin()+i, x/2+x%2);
      a.insert(a.begin()+i, x/2);
      a.insert(a.begin()+i, LPAREN);
      return 1;
    }
  return 0;
}

void reduce(vector<int> &a) {
  while (true) {
    while (explode(a));
    if (!split(a))
      return ;
  }  
}

vector<int> parse(const string &s) {
  vector<int> out;
  for (auto c : s)
    if (c == '[')
      out.push_back(LPAREN);
    else if (c == ']')
      out.push_back(RPAREN);
    else if (isdigit(c))
      out.push_back(c - '0');
  return out;
}

vector<int> add(const vector<int> &a, const vector<int> &b) {
  vector<int> out;
  out.push_back(LPAREN);
  for (auto x : a)
    out.push_back(x);
  for (auto x : b)
    out.push_back(x);
  out.push_back(RPAREN);
  return out;
}

long long magnitude(const vector<int> &a) {
  stack<long long> s;
  for (auto x : a) 
    if (x >= 0)
      s.push(x);
    else if (x == RPAREN) {
      long long r = s.top();
      s.pop();
      long long l = s.top();
      s.pop();
      s.push(3*l+2*r);             
    }
  return s.top();
}

int main() {
  vector<string> lines;
  string s;
  while (cin >> s)
    lines.push_back(s);

  long long best = -1;
  for (int i=0; i<(int)lines.size(); i++)
    for (int j=0; j<(int)lines.size(); j++)
      if (i != j) {
        vector<int> a = parse(lines[i]);
        vector<int> b = parse(lines[j]);
        a = add(a, b);
        reduce(a);
        best = max(best, magnitude(a));
      }

  cout << best << endl;
  return 0;
}
