#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>
#include <map>
#include <set>

using namespace std;

struct State {
    string node;
    int next_index;

    State(string node, int next_index) {
        this->node = node;
        this->next_index = next_index;
    }
};

void print_table(const set<pair<int, int>> &points, int max_x, int max_y) {

    for(int i = 0 ; i <= max_y ; ++i) {
        for(int j = 0 ; j <= max_x ; ++j) {
            if (points.find(make_pair(j, i)) != points.end()) cout << "#";
            else cout << ".";
        }
        cout << endl;
    }
    cout << endl;
}

void print_table(const vector<pair<int, int>> &points, int max_x, int max_y) {

    set<pair<int, int>> visited;
    for(auto p : points) {
        visited.insert(p);
    }

    for(int i = 0 ; i <= max_y ; ++i) {
        for(int j = 0 ; j <= max_x ; ++j) {
            if (visited.find(make_pair(j, i)) != visited.end()) cout << "#";
            else cout << ".";
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

    FILE *f = fopen(argv[1], "r");
    char buff[100];

    vector<pair<int, int>> points;
    int x, y;
    int max_x = 0, max_y = 0;

    while(fscanf(f, "%d,%d", &x, &y) == 2) {
        points.push_back(make_pair(x, y));
        max_x = max(x, max_x);
        max_y = max(y, max_y);
    }

    vector<pair<char, int>> fold;
    char coor;
    int where;

    while(fscanf(f, "fold along %c=%d\n", &coor, &where) == 2) {
        fold.push_back(make_pair(coor, where));
    }

    fclose(f);

    //print_table(points, max_x, max_y);

    for(int i = 0 ; i < fold.size() ; ++i) {
        char coor = fold[i].first;
        int where = fold[i].second;
        vector<pair<int, int>> new_points;
        set<pair<int, int>> visited;

        max_x = 0;
        max_y = 0;
        for(const auto &pair : points) {
            std::pair<int, int> add_pair;
            if (coor == 'x' && pair.first > where) add_pair = make_pair(2 * where - pair.first, pair.second);
            else if (coor == 'y' && pair.second > where) add_pair = make_pair(pair.first, 2 * where - pair.second);
            else add_pair = pair;

            max_x = max(max_x, add_pair.first);
            max_y = max(max_y, add_pair.second);

            if (visited.find(add_pair) == visited.end()) {
                new_points.push_back(add_pair);
                visited.insert(add_pair);
            }
        }
        points = new_points;
        print_table(visited, max_x, max_y);
        cout << visited.size() << endl;
    }

    return 0;
}
