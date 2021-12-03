#include <bits/stdc++.h>

using namespace std;

const int MAXB = 12;

vector<string> v;

int dec(const string b) {
  int ret = 0;
  for (const char bit : b) {
    ret <<= 1;
    ret += bit == '1';
  }
  return ret;
}

string rating(int bit, int lo, int hi, bool majority) {
  if (lo + 1 == hi) return v[lo];
  assert(bit < MAXB);
  int mid = lo;
  while (v[mid][bit] == '0' && mid < hi) ++mid;
  if ((mid - lo > hi - mid && majority) || (mid - lo <= hi - mid && !majority))
    return rating(bit + 1, lo, mid, majority);
  else
    return rating(bit + 1, mid, hi, majority);
}

int main(void) {
  string b;
  while (cin >> b) v.emplace_back(b);

  sort(v.begin(), v.end());

  string oxy = rating(0, 0, (int)v.size(), true);
  string co2 = rating(0, 0, (int)v.size(), false);

  cout << dec(oxy) * dec(co2) << endl;

  return 0;
}
