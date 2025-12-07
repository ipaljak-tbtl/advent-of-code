#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

string s[4];
vector<llint> x[4];
vector<string> op;

int main() {
  for (int i=0; i<4; i++)
    getline(cin, s[i]);  

  string line;
  getline(cin, line);
  istringstream iss(line);
  op = vector<string>(istream_iterator<string>(iss), istream_iterator<string>());

  llint total = 0;
  int pos = 0;
  for (int i=0; i<(int)op.size(); i++) {
    llint curr = op[i] == "+" ? 0 : 1;

    while (true) {
      llint num = 0;
      for (int j=0; j<4; j++)
        if (isdigit(s[j][pos]))
          num = num * 10 + (s[j][pos] - '0');
      pos++;
      TRACE(i _ pos _ num);
      if (num == 0) 
        break;
      if (op[i] == "+")
        curr += num;
      else  
        curr *= num;
    }

    total += curr;
  }

  cout << total << endl;
}
