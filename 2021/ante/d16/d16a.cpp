#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

vector<int> bits;

void init_bits(const string &s) {
  for (int i=(int)s.size()-1; i>=0; i--) {
    int x = stol(s.substr(i, 1), nullptr, 16);
    for (int j=0; j<4; j++) {
      bits.push_back(x&1);
      x >>= 1;
    }
  }
}

int next_int(int k) {
  assert((int)bits.size() >= k);
  int x = 0;
  for (int i=0; i<k; i++) {
    x = (x << 1) | bits.back();
    bits.pop_back();
  }
  return x;
}

int next_packet() {
  int version = next_int(3);
  int type_id = next_int(3);
  int total = version;
  if (type_id == 4) {
    int literal = 0;
    int chunk = 0xFF;
    while (chunk & 0x10) {
      chunk = next_int(5);
      literal = (literal << 4) | (chunk & 0xF);
    } 
    return total;
  }
  int length_type_id = next_int(1);
  if (length_type_id == 0) {
    int length_bits = next_int(15);
    int start_bits = bits.size();
    while (start_bits - (int)bits.size() < length_bits)
      total += next_packet();
    assert(start_bits - (int)bits.size() == length_bits);
  } else {
    int num_subpackets = next_int(11);
    for (int i=0; i<num_subpackets; i++)
      total += next_packet();
  }
  return total;
}

int main() {
  string s;
  assert(cin >> s);
  init_bits(s);
  int total = next_packet();
  cout << total << endl;       
  return 0;
}
