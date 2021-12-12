#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;

bool small[MAXN];

int n, s, t;
int cnt[MAXN];

vector<int> v[MAXN];
map<string, int> node_id;
set<vector<int>> paths;

int get_node_id(string x) {
  if (node_id.find(x) == node_id.end()) {
    node_id[x] = n;
    small[n] = x[0] >= 'a' && x[0] <= 'z';
    ++n;
  }
  return node_id[x];
}

void get_paths(int node, set<int> &visited_small,
                           vector<int> &curr_path) {
  curr_path.push_back(node);
  ++cnt[node];
  if (node == t) {
    if (cnt[s] > 1) { curr_path.pop_back(); --cnt[node]; return; }
    int tot = 0;
    for (int x = 0; x < n; ++x)
      tot += small[x] && cnt[x] > 1;
    if (tot > 1) { curr_path.pop_back(); --cnt[node]; return; }
    curr_path.pop_back();
    --cnt[node];
    paths.insert(curr_path);
    return;
  }

  set<vector<int>> ret;
  for (int nxt : v[node]) {
    if (small[nxt] && visited_small.find(nxt) != visited_small.end()) continue;
    if (small[nxt] && cnt[nxt] == 1) visited_small.insert(nxt);
    get_paths(nxt, visited_small, curr_path);
    if (small[nxt] && cnt[nxt] == 1) visited_small.erase(nxt);
  }

  curr_path.pop_back();
  --cnt[node];
}

int main(void) {
  string line;
  while (cin >> line) {
    string a = line.substr(0, line.find("-"));
    string b = line.substr(line.find("-") + 1, line.size());
    int aid = get_node_id(a), bid = get_node_id(b);
    v[aid].push_back(bid);
    v[bid].push_back(aid);
  }

  s = get_node_id("start");
  t = get_node_id("end");

  set<int> visited_small = {s};
  vector<int> curr_path;
  get_paths(s, visited_small, curr_path);

  cout << paths.size() << endl;
  return 0;
}
