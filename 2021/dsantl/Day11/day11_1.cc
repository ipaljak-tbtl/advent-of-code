#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>

using namespace std;

const int A = 3;
const int B = 57;
const int C = 1197;
const int D = 25137;

void ispis(vector<vector<int>> &map) {
    for(int i = 0 ; i < map.size() ; ++i) {
        for(int j = 0 ; j < map[i].size() ; ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void fill_me_up(char *line, vector<int> *input) {
    int size = strlen(line) - 1;
    for(int i = 0 ; i < size ; ++i) input->push_back(line[i] - '0');
}

bool make_change(int a, int b, vector<vector<int>> &map, vector<pair<int,int>> &flash) {

    bool change = false;

    int max = map.size();

    for(int i = -1 ; i <= 1 ; ++i) {
        for(int j = -1 ; j <= 1 ; ++j) {
            if (i == 0 && j == 0) continue;
            if (a + i >= max || a + i < 0) continue;
            if (b + j >= max || b + j < 0) continue;
            if (map[a + i][b + j] == 0) continue;
            map[a + i][b + j] += 1;
            if (map[a + i][b + j] > 9) {change = true; map[a + i][b + j] = 0; flash.push_back(make_pair(a + i, b + j));}
        }
    }

    return change;
}

int simulate_step(vector<vector<int>> &map) {

    vector<pair<int, int>> flash;
    vector<pair<int, int>> new_flash;
    for(int i = 0 ; i < map.size() ; ++i)
        for(int j = 0 ; j < map[i].size() ; ++j) {
            map[i][j] += 1;
            if (map[i][j] > 9) {map[i][j] = 0; flash.push_back(make_pair(i, j));}
        }


    int ret = 0;
    bool change = true;
    while(change) {
        change = false;
        for(const auto &pair : flash) {
            ++ret;
            int i = pair.first;
            int j = pair.second;
            change |= make_change(i, j, map, new_flash);
        }
        flash = new_flash;
        new_flash.clear();
    }

    ispis(map);

    return ret;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[10000];
    vector<vector<int>> map;
    while(fgets(buff, 10000, f) != NULL) {
        vector<int> row;
        fill_me_up(buff, &row);
        map.push_back(row);
    }
    fclose(f);

    ispis(map);

    int sol = 0;
    for(int i = 1 ; ; ++i) {
        sol = simulate_step(map);
        if (sol == 100) {
            cout << i << endl;
            break;
        }
    }

    return 0;
}
