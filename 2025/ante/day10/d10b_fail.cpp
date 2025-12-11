#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

template <class> struct is_container : false_type {};
template <class... Ts> struct is_container<vector<Ts...>> : true_type {};
template <class... Ts> struct is_container<map<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template <class... Ts> struct is_container<list<Ts...>> : true_type {};
template <class... Ts> struct is_container<set<Ts...>> : true_type {};
template <class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};

template<class T>
ostream& operator<< (ostream &o, tuple<T, T, T> x) {
  return o << "(" << get<0>(x) << ", " << get<1>(x) << ", " << get<2>(x) << ")";
}

template<class T, class U>
ostream& operator<< (ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}


template <class T, class = typename enable_if<is_container<T>::value>::type>
ostream& operator << (ostream &o, T x) {
  int f = 1;
  o << "[";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "]";
}

typedef long long llint;

int n;
int goal;
int m;
vector<vector<int>> switches;
vector<int> levels;

vector<pair<int, int>> single;
vector<pair<pair<int, int>, int>> without;
vector<pair<tuple<int, int, int>, int>> w2;


void init_g0() {
  single.clear();
  map<int, int> where;
  for (int i = 0; i < m; i++) 
    for (int sw : switches[i]) 
      if (!where.count(sw)) 
        where[sw] = i;
      else
        where[sw] = -1;
  for (auto [sw, idx] : where) 
    if (idx != -1) 
      single.push_back({sw, idx});
}

int g0(vector<int> &L) {
  int total = 0;
  for (auto [sw, idx] : single) {
    int cnt = L[sw];
    total += cnt;
    for (auto s : switches[idx]) {
      assert( L[s] >= cnt);
      L[s] -= cnt;
    }
  }
  return total;
}

void init_g1() {
  without.clear();
  map<pair<int, int>, int> where;
  for (int i = 0; i < m; i++) {
    set<int> all(switches[i].begin(), switches[i].end());
    for (int j1 = 0; j1 < n; j1++)
      for (int j2 = 0; j2 < n; j2++)
        if (j1 != j2 && all.count(j1) && !all.count(j2)) {
          pair<int, int> key = {j1, j2};
          if (!where.count(key))
            where[key] = i;
          else
            where[key] = -1;
        }
  }
  for (auto [key, idx] : where)
    if (idx != -1)
      without.push_back({key, idx});
}

void init_g2() {
  w2.clear();
  map<tuple<int, int, int>, int> where;
  for (int i = 0; i < m; i++) {
    set<int> all(switches[i].begin(), switches[i].end());
    for (int j1 = 0; j1 < n; j1++)
      for (int j2 = 0; j2 < n; j2++)
        for (int j3 = j2+1; j3 < n; j3++)
          if (j1 != j2 && j1 != j3 && all.count(j1) && !all.count(j2) && !all.count(j3)) {
            tuple<int, int, int> key = {j1, j2, j3};
            if (!where.count(key))
              where[key] = i;
            else
              where[key] = -1;
        }
  }
  for (auto [key, idx] : where)
    if (idx != -1)
      w2.push_back({key, idx});
}

int g1(vector<int> &L) {
  int grand_total = 0;
  int total;
  do {
    total = 0;
    for (auto [key, idx] : without) {
      int j1 = key.first;
      int j2 = key.second;
      if (L[j1] <= L[j2])
        continue;
      int cnt = L[j1]-L[j2];
      total += cnt;
      for (auto s : switches[idx]) {
        if (L[s] < cnt)
          return -1;
        L[s] -= cnt;
      }
    }
    grand_total += total;
  } while (total > 0);
  return grand_total;
}

int g2(vector<int> &L) {
  int grand_total = 0;
  int total;
  do {
    total = 0;
    for (auto [key, idx] : w2) {
      auto [j1, j2, j3] = key;
      if (L[j1] <= L[j2]+L[j3])
        continue;
      int cnt = L[j1]-L[j2]-L[j3];
      total += cnt;
      for (auto s : switches[idx]) {
        if (L[s] < cnt)
          return -1;
        L[s] -= cnt;
      }
    }
    grand_total += total;
  } while (total > 0);
  return grand_total;
}

int h1(vector<int> &L) {
  if (switches.size() < 2)
    return 0;
  int diff = switches[0].size()-switches[1].size();
  if (diff == 0) 
    return 0;
  int low = 1000;
  for (auto s : switches[0]) 
    low = min(low, L[s]);
  int cnt = max(0, low-50);
  for (auto s : switches[0]) 
    L[s] -= cnt;
  return cnt;
}

int h2(vector<int> &L) {
  int cnt = 0;
  while (true) {
    int midx = max_element(L.begin(), L.end()) - L.begin();
    if (L[midx] <= 60)
      return cnt;
    int sidx = -1;
    for (int i = 0; i < m; i++)
      if (find(switches[i].begin(), switches[i].end(), midx) != switches[i].end())
        if (switches[i].size() > switches[sidx].size() || sidx == -1)
          sidx = i;
    assert(sidx != -1);
    for (auto s : switches[sidx]) {
      if (L[s] == 0)
        return cnt;
    }
    cnt++;
    for (auto s : switches[sidx]) {
      assert(L[s] > 0);
      L[s]--;
    }
  }
}

struct VecHash {
  size_t operator()(vector<int> const& v) const {
    uint64_t h = 1469598103934665603ULL;
    for (int x : v) {
      h ^= (uint64_t)(unsigned)x;
      h *= 1099511628211ULL;
    }
    return (size_t)h;
  }
};

bool is_done(const vector<int>& s) {
  for (int x : s) 
    if (x != 0) return false;
  return true;
}

static int heuristics(const vector<int>& state) {
  int sum = 0;
  for (int x : state)
    sum += x;
  int h1 = (sum + switches[0].size() - 1) / switches[0].size();
  int h2 = *max_element(state.begin(), state.end());
  return max(h1, h2);
}

struct qelem {
  int f;
  int g;
  vector<int> state;
};

struct cmp {
  bool operator()(qelem const& a, qelem const& b) const {
    if (a.f != b.f)
      return a.f > b.f; 
    return a.g < b.g;
  }
};

int astar(const vector<int>& start) {
  if (is_done(start)) 
    return 0;

  unordered_map<vector<int>, int, VecHash> done;
  priority_queue<qelem, vector<qelem>, cmp> pq;

  int h0 = heuristics(start);
  vector<int> s = start;
  s.push_back(0);
  done[s] = 0;
  pq.push({h0, 0, s});

  size_t expansions = 0;
  while (!pq.empty()) {
    qelem cur = pq.top(); 
    pq.pop();
    vector<int> state = cur.state;
    int i = state.back();
    state.pop_back();
    auto it = done.find(cur.state);
    if (it == done.end())
      continue;
    if (cur.g != it->second)
      continue;
    if (is_done(state)) 
      return cur.g;

    bool ok = true;
    for (int s : switches[i])
      if (state[s] <= 0) { 
        ok = false; 
        break;
    }
    if (ok) {
      vector<int> nxt = state;
      for (int s : switches[i])
        nxt[s]--;   
      int ng = cur.g + 1;
      int gr1 = g1(nxt);
      int gr2 = g2(nxt);
      if (gr1 != -1 && gr2 != -1) {
        ng += gr1+gr2;        
        int nh = heuristics(nxt);
        nxt.push_back(i);
        auto git = done.find(nxt);
        if (git == done.end() || ng < git->second) {
          done[nxt] = ng;
          int nf = ng + nh;
          pq.push({nf, ng, nxt});
        }
      }
    }
    if (i < m - 1) {
      state.push_back(i + 1);
      auto git = done.find(state);
      if (git == done.end() || cur.g < git->second) {
        done[state] = cur.g;
        pq.push({cur.f, cur.g, state});
      }
    }
  }
  assert(false);
  return -1;
}

int ncase = 0;

int solve() {
  ncase++;
  for (int i=0; i<m; i++)
    for (int j=i+1; j<m; j++)
      if (switches[i].size() < switches[j].size())
        swap(switches[i], switches[j]);
  TRACE(n _ switches _ levels);
  init_g0();
  TRACE(single);
  init_g1();
  TRACE(without);
  init_g2();
  TRACE(w2);


  int g0_val = g0(levels);
  TRACE(g0_val _ levels); 
  int g1_val = g1(levels);
  int g2_val = g2(levels);
  int h1_val = 0; // h1(levels);
  int h2_val = 0; // h2(levels);
  TRACE(ncase _ n _ g1_val _ g2_val _ h1_val _ h2_val _ levels _ switches);
  int astar_val = astar(levels);
  TRACE(astar_val);
  return g0_val + g1_val + g2_val + h1_val + h2_val + astar_val;
}

int main() {
  int total = 0;
  string item;

  while (cin >> item) {
    string inside = item.substr(1, item.size()-2);
    if (item[0] == '[') {
      n = inside.size();
      switches.clear();
      levels.clear();
    } else if (item[0] == '(') {
      switches.push_back(vector<int>());
      for (const auto word : std::views::split(inside, ',')) {
        int a = stoi(string(string_view(word)));
        switches.back().push_back(a);
      }
    } else if (item[0] == '{') {
      for (const auto word : std::views::split(inside, ',')) {
        int a = stoi(string(string_view(word)));
        levels.push_back(a);
      }
      m = switches.size();
      total += solve();
    }
  }

  cout << total << endl;
  return 0;
}
