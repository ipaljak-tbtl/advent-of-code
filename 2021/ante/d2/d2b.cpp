#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

int main() {
  int cx = 0;
  int cy = 0;
  int aim = 0;
  string command;
  int value = 0;
  while (cin >> command >> value) {
    if (command == "forward")
      cx += value, cy += value*aim;
    else if (command == "down")
      aim += value;
    else if (command == "up")
      aim -= value;    
  }
  cout << cx*cy << endl;
  return 0;
}
