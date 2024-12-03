#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <class T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

#define TRACE(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#define _ << " _ " <<

template <class T, class U> ostream &operator<<(ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}
template <class> struct is_container : false_type {};
template <class... Ts> struct is_container<vector<Ts...>> : true_type {};
template <class... Ts> struct is_container<map<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template <class... Ts> struct is_container<set<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template <class... Ts> struct is_container<multiset<Ts...>> : true_type {};
template <class... Ts>
struct is_container<unordered_multiset<Ts...>> : true_type {};
template <class T, class = typename enable_if<is_container<T>::value>::type>
ostream &operator<<(ostream &o, T x) {
  int f = 1;
  o << "{";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "}";
}

typedef long long llint;

bool enabled = true;
char s[1024];
int n, ptr, sol;

bool parse_str(const char *target) {
  for (int i = 0; i < strlen(target); ++i)
    if (ptr + i >= n || s[ptr + i] != target[i])
      return false;
  ptr += strlen(target);
  return true;
}

int parse_num() {
  int ret = 0;
  while (ptr < n && isdigit(s[ptr]))
    ret = ret * 10 + s[ptr++] - '0';
  return ret;
}

void try_mul() {
  int op1, op2;

  if (!parse_str("("))
    return;

  if (ptr >= n || !isdigit(s[ptr]))
    return;

  op1 = parse_num();

  if (!parse_str(","))
    return;

  if (ptr >= n || !isdigit(s[ptr]))
    return;

  op2 = parse_num();

  if (!parse_str(")"))
    return;

  sol += op1 * op2 * enabled;
}

int main(void) {
  while (scanf("%s", s) == 1) {
    ptr = 0;
    n = strlen(s);

    while (ptr < n) {
      if (parse_str("do()"))
        enabled = true;
      if (parse_str("don't()"))
        enabled = false;
      if (parse_str("mul")) {
        try_mul();
        continue;
      }
      ++ptr;
    }
  }
  printf("%d\n", sol);
  return 0;
}
