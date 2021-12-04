#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

vector<int> read_csv() {
  string line;
  vector<int> result;
  if (!(cin >> line))
    return result;
  istringstream in(line);
  int value = 0;
  while (in >> value) {
    result.push_back(value);
    char c;
    in >> c;
    assert(c == ',');
  }
  return result;
}

int read_board(int board[5][5]) {
  for (int i=0; i<5; i++)
    for (int j=0; j<5; j++)
      if (!(cin >> board[i][j]))
        return 0;
  return 1;
}

int done(int board[5][5]) {
  for (int i=0; i<5; i++) {
    int cnt = 0;
    for (int j=0; j<5; j++)
      if (board[i][j] == -1)
        cnt++;
    if (cnt == 5)
      return 1;
  }
  for (int i=0; i<5; i++) {
    int cnt = 0;
    for (int j=0; j<5; j++)
      if (board[j][i] == -1)
        cnt++;
    if (cnt == 5)
      return 1;
  }
  return 0;
}

pair<int, int> play(int board[5][5], vector<int> numbers) {
  int sum = 0;
  for (int i=0; i<5; i++)
    for (int j=0; j<5; j++)
      sum += board[i][j];
  
  for (int k=0; k<(int)numbers.size(); k++) {
    for (int i=0; i<5; i++)
      for (int j=0; j<5; j++)
        if (board[i][j] == numbers[k]) {
          sum -= board[i][j];
          board[i][j] = -1;
        }
    if (done(board))
      return {k+1, sum*numbers[k]};
  }
  
  return {-1, -1};
}

int main() {
  vector<int> numbers = read_csv();
  int win_moves = -1;
  int win_score = -1;

  int board[5][5];
  while (read_board(board)) {
      auto [moves, score] = play(board, numbers);
      if (win_moves == -1 || moves > win_moves)
        win_moves = moves, win_score = score;
  }
  
  cout << win_moves << " " << win_score << endl;  
  return 0;
}
