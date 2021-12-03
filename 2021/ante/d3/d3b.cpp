#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int len = 0;
vector<int> freq;

int find(int k) {
  int current = 0;
  for (int j=0; j<len; j++) {
    int f0 = freq[(current<<1)|(1<<(j+1))];
    int f1 = freq[(current<<1)|(1<<(j+1))|1];
    assert(f0 || f1);
    
    int next = 0;
    if (f0 == 0)
      next = 1;
    else if (f1 == 0)
      next = 0;
    else if (k == 0 && (f1 >= f0))
      next = 1;
    else if (k == 1 && (f1 < f0))
      next = 1;
    else
      next = 0;
    current = (current<<1) | next;
  }
  return current;
}
  
int main() {
  string line;
  while (cin >> line) {
    if (len == 0) {
      len = line.size();
      freq = vector<int>(1<<(len+1));
    }
    assert((int)line.size() == len);
    int value = stoi(line, nullptr, 2);
    for (int i=len; i>0; i--) {
      freq[value|(1<<i)]++;
      value >>= 1;
    } 
  }

  cout << find(0)*find(1) << endl;
  return 0;
}
