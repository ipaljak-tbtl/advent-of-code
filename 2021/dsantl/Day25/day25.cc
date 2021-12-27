#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <sstream>

using namespace std;

void print(const vector<vector<char>> &map) {
    for(int i = 0 ; i < map.size() ; ++i) {
        for(int j = 0 ; j < map[i].size() ; ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    vector<vector<char>> map;

    FILE *f = fopen(argv[1], "r");
    char buff[150];
    while(fscanf(f, "%s", buff) != EOF) {
        int size = strlen(buff);
        vector<char> row;
        for(int i = 0 ; i < size ; ++i) {
            row.push_back(buff[i]);
        }
        map.push_back(row);
    }
    fclose(f);

    int max_row = map.size();
    int max_col = map[0].size();

    for(int k = 1 ; ; ++k) {
        auto new_map = map;

        bool change = false;
        for(int i = 0; i < max_row ; ++i) {
            for(int j = 0 ; j < max_col ; ++j) {
                if (map[i][j] == '>' && map[i][(j + 1) % max_col] == '.') {
                    change = true;
                    new_map[i][j] = '.';
                    new_map[i][(j + 1) % max_col] = '>';
                }
            }
        }

        map = new_map;

        for(int i = 0; i < max_row ; ++i) {
            for(int j = 0 ; j < max_col ; ++j) {
                if (map[i][j] == 'v' && map[(i + 1) % max_row][j] == '.') {
                    change = true;
                    new_map[i][j] = '.';
                    new_map[(i + 1) % max_row][j] = 'v';
                }
            }
        }

        map = new_map;

        if (!change) {cout << k << endl; break;}
    }

    return 0;
}
