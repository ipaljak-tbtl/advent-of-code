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

long long init(int type_id) {
  if (type_id == 0)
    return 0;
  else if (type_id == 1)
    return 1;
  else if (type_id == 2)
    return -1;
  else if (type_id == 3)
    return -1;
  else if (type_id == 5)
    return -1;
  else if (type_id == 6)
    return -1;
  else if (type_id == 7)
    return -1;
  assert(false);
}

long long process(int type_id, long long value, long long total) {
  if (type_id == 0)
    return total + value;
  else if (type_id == 1)
    return total * value;
  else if (type_id == 2)
    return total == -1? value : min(total, value);
  else if (type_id == 3)
    return total == -1? value : max(total, value);
  else if (type_id == 5)
    return total == -1? value : total > value;
  else if (type_id == 6)
    return total == -1? value : total < value;
  else if (type_id == 7)
    return total == -1? value : total == value;
  assert(false);
}

long long next_packet() {
  int version = next_int(3);
  int type_id = next_int(3);
  
  if (type_id == 4) {
    long long literal = 0;
    int chunk = 0xFF;
    while (chunk & 0x10) {
      chunk = next_int(5);
      literal = (literal << 4) | (chunk & 0xF);
    } 
    return literal;
  }

  long long total = init(type_id);
  int length_type_id = next_int(1);

  if (length_type_id == 0) {
    int length_bits = next_int(15);
    int start_bits = bits.size();
      while (start_bits - (int)bits.size() < length_bits) {
      long long value = next_packet();
      total = process(type_id, value, total);
    }
    assert(start_bits - (int)bits.size() == length_bits);
  } else {
    int num_subpackets = next_int(11);
    for (int i=0; i<num_subpackets; i++) {
      long long value = next_packet();
      total = process(type_id, value, total);
    }
  }
  
  return total;
}

int main() {
  string s;
  assert(cin >> s);
  init_bits(s);
  long long total = next_packet();
  cout << total << endl;       
  return 0;
}
