#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

vector<llint> x[4];
vector<string> op;

int main() {
  for (int i=0; i<4; i++) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    x[i] = vector<llint>(istream_iterator<llint>(iss), istream_iterator<llint>());
  }

  string line;
  getline(cin, line);
  istringstream iss(line);
  op = vector<string>(istream_iterator<string>(iss), istream_iterator<string>());

  llint total = 0;
  for (int i=0; i<(int)op.size(); i++) {
    if (op[i] == "+") 
      total += x[0][i] + x[1][i] + x[2][i] + x[3][i];
    else
      total += x[0][i] * x[1][i] * x[2][i] * x[3][i];
  }

  cout << total << endl;
}
