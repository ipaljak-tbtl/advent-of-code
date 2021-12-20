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

struct State {
    set<pair<int, int>> map;
    bool invert = false;
    int min_x, min_y, max_x, max_y;
    char *algorithm;

    void update_border() {
        bool first = true;
        for(const auto &pair : map) {
            int x = pair.first;
            int y = pair.second;
            if (first) {
                min_x = max_x = x;
                min_y = max_y = y;
                first = false;
            }
            min_x = min(min_x, x);
            max_x = max(max_x, x);
            min_y = min(min_y, y);
            max_y = max(max_y, y);
        }

        min_x -= 3;
        min_y -= 3;
        max_x += 3;
        max_y += 3;
    }
};

char get_value(const pair<int, int> &coor, const State &state) {

    bool exists = state.map.find(coor) != state.map.end();

    if (exists && !state.invert) return '#';
    if (exists && state.invert) return  '.';
    if (!exists && !state.invert) return '.';
    return '#';
}

void print_state(State &state) {
    state.update_border();

    for(int y = state.min_y ; y <= state.max_y ; ++y) {
        for(int x = state.min_x ; x <= state.max_x ; ++x) {
            cout << get_value(make_pair(x, y), state);
        }
        cout << endl;
    }
}

char do_algorithm(int x, int y, const State &state) {

    int curr_pow = 256;
    int ret = 0;
    for(auto dy : {-1, 0, 1}) {
        for(auto dx : {-1, 0, 1}) {
            if (get_value(make_pair(x + dx, y + dy), state) == '#') ret += curr_pow;
            curr_pow >>= 1;
        }
    }
    return state.algorithm[ret];
}

void do_step(State &state) {

    state.update_border();
    bool new_invert = state.invert;

    if (!state.invert && state.algorithm[0] == '#') new_invert = true;
    if (state.invert && state.algorithm[511] == '.') new_invert = false;

    set<pair<int, int>> new_map;
    int min_x, min_y, max_x, max_y;

    for(int x = state.min_x ; x <= state.max_x ; ++x) {
        for(int y = state.min_y ; y <= state.max_y ; ++y) {
            char sign = do_algorithm(x, y, state);
            if (sign == '#' && !new_invert) new_map.insert(make_pair(x, y));
            if (sign == '.' && new_invert) new_map.insert(make_pair(x, y));
        }
    }

    state.map = new_map;
    state.invert = new_invert;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    char algorithm[514];

    FILE *f = fopen(argv[1], "r");
    fscanf(f, "%s", algorithm);


    State state;
    state.algorithm = algorithm;

    char buff[1000];
    int row = 0;
    int size;
    while(fscanf(f, "%s", buff) != EOF) {
        if (row == 0) size = strlen(buff);
        for(int col = 0 ; col < size ; ++col) {
            if (buff[col] != '#') continue;
            if (row == 0 && col == 0) {state.min_x = state.max_x = col; state.min_y = state.max_y = row;}
            state.map.insert(make_pair(col, row));
        }
        row++;
    }
    fclose(f);

    print_state(state);
    cout << endl;

    do_step(state);
    do_step(state);

    if (state.invert) {
        cout << "INF!" << endl;
        return 0;
    }

    print_state(state);

    cout << state.map.size() << endl;

    return 0;
}
