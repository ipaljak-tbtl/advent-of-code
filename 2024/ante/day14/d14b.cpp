#include <bits/stdc++.h>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

typedef long long llint;

const int NX = 101;
const int NY = 103;

vector<int> x;
vector<int> y;
vector<int> dx;
vector<int> dy;


void display() {
  vector<string> grid(NY, string(NX, ' '));
  for (int i=0; i<(int)x.size(); i++) {
    grid[y[i]][x[i]] = '#';
  }
  for (auto s : grid)
    cout << s << endl;
  cout << endl;
}


int score() {
  int total = 0;
  for (int i = 0; i < (int)x.size(); i++) {
    int min_dist = 1e9;
    for (int j = 0; j < (int)x.size(); j++) {
      if (i == j) continue;
      int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
      min_dist = min(min_dist, dist);
    }
    total += min_dist;
  }
  return total;

}


int main() {
  int ax, ay, adx, ady;
  while (scanf(" p=%d,%d v=%d,%d", &ax, &ay, &adx, &ady) == 4) {
    x.push_back(ax);
    y.push_back(ay);
    dx.push_back(adx);
    dy.push_back(ady);
  }

  int best_score = 1e9;
  for (int t=0; t<101*103; t++) {
    for (int i=0; i<(int)x.size(); i++) {
      x[i] = ((x[i]+dx[i])%NX+NX)%NX;
      y[i] = ((y[i]+dy[i])%NY+NY)%NY;
    }

    int s = score();
    if (s < best_score) {
      best_score = s;
      cout << t+1 << " " << best_score << endl;
      display();
    }
  }

  return 0;
}

