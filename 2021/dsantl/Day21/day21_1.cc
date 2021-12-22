#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <cmath>
#include <tuple>

using namespace std;

const int TABLE_SIZE = 10;

map<tuple<int, int, int, int, int, int>, pair<long long int, long long int>> memo;

pair<long long int, long long int> rec(tuple<int, int, int, int, int, int> state) {

    if (memo.find(state) != memo.end()) return memo[state];

    auto [p1, p2, turn, s1, s2, counter] = state;

    if (s1 >= 21) return make_pair(1, 0);
    if (s2 >= 21) return make_pair(0, 1);

    long long int u1 = 0;
    long long int u2 = 0;

    if (counter == 3) {
        turn = 1 - turn;
        counter = 0;
    }

    int mul = 0;
    if (counter == 2) mul = 1;

    if (turn == 0) {
        int position = (p1 + 1 - 1) % TABLE_SIZE + 1;
        int score = s1 + position * mul;
        auto sol1 = rec({position, p2, turn, score, s2, counter + 1});

        position = (p1 + 2 - 1) % TABLE_SIZE + 1;
        score = s1 + position * mul;
        auto sol2 = rec({position, p2, turn, score, s2, counter + 1});

        position = (p1 + 3 - 1) % TABLE_SIZE + 1;
        score = s1 + position * mul;
        auto sol3 = rec({position, p2, turn, score, s2, counter + 1});

        u1 = sol1.first + sol2.first + sol3.first;
        u2 = sol1.second + sol2.second + sol3.second;
    }
    else {
        int position = (p2 + 1 - 1) % TABLE_SIZE + 1;
        int score = s2 + position * mul;
        auto sol1 = rec({p1, position, turn, s1, score, counter + 1});

        position = (p2 + 2 - 1) % TABLE_SIZE + 1;
        score = s2 + position * mul;
        auto sol2 = rec({p1, position, turn, s1, score, counter + 1});

        position = (p2 + 3 - 1) % TABLE_SIZE + 1;
        score = s2 + position * mul;
        auto sol3 = rec({p1, position, turn, s1, score, counter + 1});

        u1 = sol1.first + sol2.first + sol3.first;
        u2 = sol1.second + sol2.second + sol3.second;
    }

    auto pair = make_pair(u1, u2);
    memo[state] = pair;
    return pair;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    int players[2];

    FILE *f = fopen(argv[1], "r");
    fscanf(f, "Player 1 starting position: %d\n", &players[0]);
    fscanf(f, "Player 2 starting position: %d\n", &players[1]);
    fclose(f);

    auto sol = rec({players[0], players[1], 0, 0, 0, 0});

    cout << max(sol.first, sol.second) << endl;

    return 0;
}
