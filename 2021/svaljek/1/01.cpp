#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream input{"./input.txt"};
  unsigned count{0}, depth{0}, current{0};

  while (input >> depth) {
      if (depth > current) count++;
      current = depth;
  }

  cout << "Depth increased " << count - 1 << " times.\n";
}
