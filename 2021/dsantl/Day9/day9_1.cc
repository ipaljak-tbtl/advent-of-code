#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <queue>

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

bool check_neigh(vector<vector<int>> &map, vector<vector<int>> &visited, int i, int j, int n_i, int n_j) {
    if (n_i >= map.size()) return false;
    if (n_j >= map.at(i).size()) return false;
    if (n_i < 0) return false;
    if (n_j < 0) return false;

    if (visited[n_i][n_j] == 1) return false;
    if (map[n_i][n_j] == 9) return false;
    if (map[i][j] >= map[n_i][n_j]) return false;

    return true;
}

int bfs(vector<vector<int>> &map, vector<vector<int>> &visited, int i, int j) {

    if (low_check(map, i, j) == 0) return -1;
    if (visited[i][j] == 1) return -1;
    if (map[i][j] == 9) return -1;

    int size = 0;
    queue<pair<int, int>> q;

    q.push(make_pair(i, j));

    while(!q.empty()) {
        auto front = q.front();
        i = front.first; j = front.second;
        q.pop();
        if (visited[i][j] == 1) continue;
        size++;
        visited[i][j] = 1;
        if (check_neigh(map, visited, i, j, i + 1, j)) q.push(make_pair(i + 1, j));
        if (check_neigh(map, visited, i, j, i - 1, j)) q.push(make_pair(i - 1, j));
        if (check_neigh(map, visited, i, j, i, j + 1)) q.push(make_pair(i, j + 1));
        if (check_neigh(map, visited, i, j, i, j - 1)) q.push(make_pair(i, j - 1));
    }
    return size;
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

    auto visited = map;
    for(int i = 0 ; i < visited.size() ; ++i)
        for(int j = 0 ; j < visited.at(i).size() ; ++j)
            visited[i][j] = 0;

    vector<int> basin_size;
    int count;
    for(int i = 0 ; i < map.size() ; ++i) {
        for(int j = 0 ; j < map.at(i).size() ; ++j) {
            count = bfs(map, visited, i, j);
            if (count < 0) continue;
            basin_size.push_back(count);
        }
    }

    sort(basin_size.begin(), basin_size.end(), greater<int>());
    cout << basin_size[0] * basin_size[1] * basin_size[2] << endl;
    return 0;
}
