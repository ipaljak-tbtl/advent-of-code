#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream input{"./input.txt"};
  unsigned count{0}, depth{0}, next{0};
  unsigned window[3] = {0};

  input >> window[0];
  input >> window[1];
  input >> window[2];
  unsigned current = window[0] + window[1] + window[2];

  while (input >> depth) {
      next = window[1] + window[2] + depth;
      if (next > current) count++;
      window[0] = window[1];
      window[1] = window[2];
      window[2] = depth;
      current = next;
  }

  cout << "Depth increased " << count << " times.\n";
}
