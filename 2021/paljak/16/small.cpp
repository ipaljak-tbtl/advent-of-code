#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2010;

struct Packet {
  int version, type_id, size;
  vector<Packet> subpacket;

  Packet() {}
  Packet(int version, int type_id, int size, vector<Packet> subpacket)
      : version(version),
        type_id(type_id),
        size(size),
        subpacket(subpacket) {}
};

int n, version_sum;
char s[MAXN];

string bits;

string binary(char c) {
  if (c == '0') return "0000";
  if (c == '1') return "0001";
  if (c == '2') return "0010";
  if (c == '3') return "0011";
  if (c == '4') return "0100";
  if (c == '5') return "0101";
  if (c == '6') return "0110";
  if (c == '7') return "0111";
  if (c == '8') return "1000";
  if (c == '9') return "1001";
  if (c == 'A') return "1010";
  if (c == 'B') return "1011";
  if (c == 'C') return "1100";
  if (c == 'D') return "1101";
  if (c == 'E') return "1110";
  if (c == 'F') return "1111";
}

Packet packet;

int bin2int(int lo, int hi) {
  int ret = 0;
  for (int i = lo; i < hi; ++i) {
    ret <<= 1;
    ret |= bits[i] == '1';
  }
  return ret;
}

Packet parse(int i) {
  int version = bin2int(i, i + 3);
  version_sum += version;
  i += 3;
  assert(i < n);

  int type_id = bin2int(i, i + 3);
  i += 3;
  assert(i < n);

  if (type_id == 4) {
    int size = 3 + 3;
    while (bits[i] != '0') {
      size += 5;
      i += 5;
      assert(i < n);
    }
    assert(i + 5 < n);
    return Packet(version, type_id, size + 5, {});
  }

  int length_type_id = bin2int(i, i + 1);
  i += 1;
  assert(i < n);

  if (length_type_id == 0) {
    int subpacket_size = bin2int(i, i + 15);
    i += 15;
    assert(i < n);

    vector<Packet> subpacket;
    int sz = 0;
    while (sz < subpacket_size) {
      subpacket.emplace_back(parse(i));
      i += subpacket.rbegin()->size;
      sz += subpacket.rbegin()->size;
      assert(i < n);
    }

    assert(sz == subpacket_size);
    return Packet(version, type_id, 3 + 3 + 1 + 15 + subpacket_size, subpacket);
  } else {
    int subpacket_cnt = bin2int(i, i + 11);
    i += 11;
    assert(i < n);

    int size = 3 + 3 + 1 + 11;
    vector<Packet> subpacket;
    while (subpacket_cnt) {
      subpacket.emplace_back(parse(i));
      size += subpacket.rbegin()->size;
      i += subpacket.rbegin()->size;
      assert(i < n);
      --subpacket_cnt;
    }

    return Packet(version, type_id, size, subpacket);
  }
}

int main(void) {
  scanf("%s", s);
  n = strlen(s);

  for (int i = 0; i < n; ++i) bits += binary(s[i]);

  n = bits.size();
  packet = parse(0);

  printf("%d\n", version_sum);
  return 0;
}
