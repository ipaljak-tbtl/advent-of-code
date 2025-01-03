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

using namespace std;

void fill_me_up(char *buff, vector<vector<int>> *input) {
    vector<int> row;
    int size = strlen(buff);
    for(int i = 0 ; i < size ; ++i) {
        row.push_back(buff[i] - '0');
    }
    input->push_back(row);
}

int gmap(const vector<vector<int>> &map, int i, int j) {
    const int SIZE = 5 * map.size();

    int add_i = i / map.size();
    int add_j = j / map.size();

    int ret = (add_i + add_j) + map[i % map.size()][j % map.size()];
    return (ret - 1) % 9 + 1;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    vector<vector<int>> map;

    char buff[105];
    FILE *f = fopen(argv[1], "r");
    while(fscanf(f, "%s", buff) != EOF) {
        fill_me_up(buff, &map);
    }
    fclose(f);

    int sol;
    set<pair<int, int>> visited;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
    q.push(make_pair(0, make_pair(0, 0)));

    const int SIZE = 5 * map.size();

    while(!q.empty()) {
        auto top = q.top();
        q.pop();
        int i = top.second.first;
        int j = top.second.second;

        if (i == SIZE - 1 && j == SIZE - 1) {sol = top.first; break;}

        if (visited.find(top.second) != visited.end()) continue;

        visited.insert(top.second);

        for(int d : {-1, 1}) {
            if (i + d >= 0 && i + d < SIZE) q.push(make_pair(top.first + gmap(map, i + d, j), make_pair(i + d, j)));
            if (j + d >= 0 && j + d < SIZE) q.push(make_pair(top.first + gmap(map, i, j + d), make_pair(i, j + d)));
        }

    }

    cout << sol << endl;

    return 0;
}
