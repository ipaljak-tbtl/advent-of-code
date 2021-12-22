#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

vector<int> S;
vector<int> X1;
vector<int> X2;
vector<int> Y1;
vector<int> Y2;
vector<int> Z1;
vector<int> Z2;
vector<int> CX;
vector<int> CY;
vector<int> CZ;
unordered_map<int, int> ON;

typedef unsigned long long ullint;

int main() {
  char s[1024];
  int x1, x2;
  int y1, y2;
  int z1, z2;
  while (scanf(" %s x=%d..%d,y=%d..%d,z=%d..%d", s, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
    if (x1 > x2)
      swap(x1, x2);
    if (y1 > y2)
      swap(y1, y2);
    if (z1 > z2)
      swap(z1, z2);
    S.push_back(s[1] == 'n');
    X1.push_back(x1);
    X2.push_back(x2);
    Y1.push_back(y1);
    Y2.push_back(y2);
    Z1.push_back(z1);
    Z2.push_back(z2);
    CX.push_back(x1);
    CX.push_back(x2+1);
    CY.push_back(y1);
    CY.push_back(y2+1);
    CZ.push_back(z1);
    CZ.push_back(z2+1);
  }

  sort(CX.begin(), CX.end());
  CX.erase(unique(CX.begin(), CX.end()), CX.end());

  sort(CY.begin(), CY.end());
  CY.erase(unique(CY.begin(), CY.end()), CY.end());

  sort(CZ.begin(), CZ.end());
  CZ.erase(unique(CZ.begin(), CZ.end()), CZ.end());
  
  ullint cnt = 0;
  for (int i=0; i<(int)X1.size(); i++) {
    for (auto a=lower_bound(CX.begin(), CX.end(), X1[i]); *a <= X2[i]; ++a)
      for (auto b=lower_bound(CY.begin(), CY.end(), Y1[i]); *b <= Y2[i]; ++b)
        for (auto c=lower_bound(CZ.begin(), CZ.end(), Z1[i]); *c <= Z2[i]; ++c) {
          int key = ((a-CX.begin())*1000+b-CY.begin())*1000+c-CZ.begin();
          int old = ON[key];
          ON[key] = S[i];
          ullint vol = ((ullint)*(a+1)-*a)*((ullint)*(b+1)-*b)*((ullint)*(c+1)-*c);
          cnt += (S[i]-old)*vol;
        }          
  }
  
  cout << cnt << endl;
        
  return 0;
}
