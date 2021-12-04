#include <bits/stdc++.h>

using namespace std;

class Board {
 public:
  Board() : score(-1) {}

  void append(int x) { nums.push_back(x); }

  int cross(int x) {
    if (score != -1) return -1;

    for (int i = 0; i < 25; ++i)
      if (nums[i] == x) nums[i] = -1;

    for (int i = 0; i < 5; ++i) {
      bool row = true, col = true;
      for (int j = 0; j < 5; ++j) {
        row &= nums[5 * i + j] == -1;
        col &= nums[5 * j + i] == -1;
      }
      if (row || col) update_score();
    }

    return score;
  }

 private:
  void update_score() {
    score = 0;
    for (int x : nums)
      if (x != -1) score += x;
  }

  int score;
  vector<int> nums;
};

vector<int> v;
vector<Board> b;

void parse_nums() {
  string s;
  cin >> s;
  int curr = 0;
  for (const char c : s) {
    if (c == ',') {
      v.push_back(curr);
      curr = 0;
      continue;
    }
    curr *= 10;
    curr += c - '0';
  }
  v.push_back(curr);
}

void parse_boards() {
  Board curr;
  int num, cnt = 0;
  while (cin >> num) {
    if (cnt == 25) {
      b.push_back(curr);
      cnt = 0;
      curr = Board();
    }
    curr.append(num);
    ++cnt;
  }
  b.push_back(curr);
}

int main(void) {
  parse_nums();
  parse_boards();

  for (int num : v) {
    for (auto &board : b) {
      int score = board.cross(num);
      if (score != -1) {
        printf("%d\n", num * score);
        return 0;
      }
    }
  }

  assert(false);

  return 0;
}
