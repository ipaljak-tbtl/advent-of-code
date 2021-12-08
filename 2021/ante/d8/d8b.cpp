#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

const vector<string> DISPLAY = {
  "abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg"
};
map<int, int> HASH_TO_SEGMENT;

vector<int> hash_digits(const vector<string> &digits) {
  vector<int> result;
  for (char c='a'; c<='g'; c++) {
    vector<int> freq;
    for (int i=0; i<(int)digits.size(); i++)
      if (digits[i].find(c) != string::npos)
        freq.push_back(digits[i].size());    
    sort(freq.begin(), freq.end());
    int h = 0;
    for (auto a : freq)
      h = h*10+a;
    result.push_back(h);
  }
  return result;
}

int decode(vector<string> query, const vector<int> &segments) {
  for (auto &s : query) {
    for (auto &c : s)
      c = 'a'+segments[c-'a'];
    sort(s.begin(), s.end());
  }
  int result = 0;
  for (auto &s : query) {
    int index = find(DISPLAY.begin(), DISPLAY.end(), s)-DISPLAY.begin();
    assert(index < (int)DISPLAY.size());
    result = result*10+index;
  }
  return result;
}

int read_input(vector<string> &digits, vector<string> &query) {
  digits.resize(10);
  query.resize(4);
  for (int i=0; i<10; i++)
    if (!(cin >> digits[i]))
        return 0;        
  string s;
  cin >> s;
  assert(s == "|");
  for (int i=0; i<4; i++)
    if (!(cin >> query[i]))
      return 0;
  return 1;
}

int main() {
  vector<int> display_hash = hash_digits(DISPLAY);
  for (int i=0; i<(int)display_hash.size(); i++)
    HASH_TO_SEGMENT[display_hash[i]] = i;

  vector<string> digits;
  vector<string> query;
  int total = 0;
  while (read_input(digits, query)) {
    vector<int> digit_hash = hash_digits(digits);
    vector<int> segments;
    for (int i=0; i<(int)digit_hash.size(); i++)
      segments.push_back(HASH_TO_SEGMENT[digit_hash[i]]);
    int value = decode(query, segments);
    total += value;
  }
  
  cout << total << endl;
  return 0;
}
