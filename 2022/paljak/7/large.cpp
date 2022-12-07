#include <bits/stdc++.h>

using namespace std;

const int DISK_SIZE = 70000000;
const int SPACE_NEEDED = 30000000;

struct Dir {
  int size, total = -1;
  string name;
  Dir* parent;
  vector<Dir*> subdirs;

  Dir() {}
  Dir(string name) : name(name) {}
  Dir(string name, Dir* parent) : name(name), parent(parent) {}

  optional<Dir*> get_subdir(string name) {
    for (Dir *subdir : subdirs)
      if (subdir->name == name) return optional<Dir*>(subdir);
    return nullopt;
  }

  Dir* add_subdir(string name) {
    if (auto subdir = get_subdir(name))
      return subdir.value();
    auto nxt_dir = new Dir(name, this);
    subdirs.emplace_back(nxt_dir);
    return nxt_dir;
  }

  int total_size() {
    if (total != -1) return total;
    total = size;
    for (Dir *subdir : subdirs)
      total += subdir->total_size();
    return total;
  }
};

Dir *root = new Dir("/"), *curr;

void parse_cd() {
  string nxt;
  cin >> nxt;
  if (nxt == "/") {
    curr = root;
    return;
  }
  if (nxt == "..") {
    curr = curr->parent;
    return;
  }
  if (auto nxt_dir = curr->get_subdir(nxt)) {
    curr = nxt_dir.value();
    return;
  }
  curr = curr->add_subdir(nxt);
}

void parse_ls() {
  while (true) {
    string a, b;
    if (!(cin >> a) || a == "$") {
      cin.putback('$');
      break;
    }
    cin >> b;
    if (a == "dir")
      curr->add_subdir(b);
    else
      curr->size += stoi(a);
  }
}

int mem_deleted(Dir *curr, int to_free) {
  int ret = DISK_SIZE;
  if (curr->total_size() < to_free) return ret;
  ret = curr->total_size();
  for (Dir *nxt : curr->subdirs)
    ret = min(ret, mem_deleted(nxt, to_free));
  return ret;
}


int main(void) {
  string token;
  root->parent = root;
  curr = root;
  while (cin >> token) {
    assert(token == "$");
    string cmd;
    cin >> cmd;
    if (cmd == "cd") parse_cd();
    if (cmd == "ls") parse_ls();
  }

  cout << mem_deleted(root, SPACE_NEEDED - (DISK_SIZE - root->total_size())) << endl;

  return 0;
}
