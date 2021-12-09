#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>

using namespace std;

void fill_me_up(char *input, vector<vector<int>> &map) {
    int size = strlen(input) - 1;
    map.push_back({});
    for(int i = 0 ; i < size ; ++i) {
        map.back().push_back(input[i] - '0');
    }
}


int low_check(vector<vector<int>> &map, int i, int j) {
    bool check = true;

    if (i - 1 >= 0 && map[i][j] >= map[i - 1][j]) check = false;

    if (i + 1 < map.size() && map[i][j] >= map[i + 1][j]) check = false;

    if (j - 1 >= 0 && map[i][j] >= map[i][j - 1]) check = false;

    if (j + 1 < map.at(i).size() && map[i][j] >= map[i][j + 1]) check = false;

    if (check) return map[i][j] + 1;
    return 0;
}



int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[10000];
    vector<vector<int>> map;
    while(fgets(buff, 10000, f) != NULL) fill_me_up(buff, map);
    fclose(f);

    int count = 0;
    for(int i = 0 ; i < map.size() ; ++i) {
        for(int j = 0 ; j < map.at(i).size() ; ++j) {
            count += low_check(map, i, j);
        }
    }

    cout << count << endl;
    return 0;
}
