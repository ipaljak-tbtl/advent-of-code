#include <bits/stdc++.h>

using namespace std;

vector<string> stack_lines;
vector<stack<char>> stacks;

void parse_stack_lines() {
  for (int j = 0; j < (int) stack_lines[0].size(); ++j) {
    if (stack_lines[stack_lines.size() - 2][j] - '0' != stacks.size() + 1)
      continue;
    stacks.emplace_back(stack<char>());
    for (int i = stack_lines.size() - 3; i >= 0; --i) {
      if (stack_lines[i][j] != ' ')
        stacks.rbegin()->push(stack_lines[i][j]);
    }
  }
}

int main(void) {
  string line;
  do {
    getline(cin, line);
    stack_lines.emplace_back(line);
  } while (!line.empty());

  parse_stack_lines();

  int k, from, to;
  while (scanf("move %d from %d to %d\n", &k, &from, &to) != EOF) {
    --from; --to;
    stack<char> tmp;
    for (int i = 0; i < k; ++i) {
      tmp.push(stacks[from].top());
      stacks[from].pop();
    }
    while (!tmp.empty()) {
      stacks[to].push(tmp.top());
      tmp.pop();
    }
  }

  for (auto &st : stacks)
    if (!st.empty())
      printf("%c", st.top());

  printf("\n");
  return 0;
}
