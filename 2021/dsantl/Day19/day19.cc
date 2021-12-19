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

struct Coordinate {
    int x, y, z;

    Coordinate(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Transformation {
    vector<int> x, y, z;
    Transformation() {};
    Transformation(vector<int> x, vector<int> y, vector<int> z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Joiner {
    int first;
    int second;
    int dx, dy, dz;
    Transformation t;

    Joiner() {}

    Joiner(int first, int second, int dx, int dy, int dz, Transformation t) {
        this->first = first;
        this->second = second;
        this->dx = dx;
        this->dy = dy;
        this->dz = dz;
        this->t = t;
    }
};

void get_deltas(int &dx, int &dy, int &dz, Coordinate &a, Coordinate &b, Transformation &t) {
    int new_x = t.x[0] * b.x + t.y[0] * b.y + t.z[0] * b.z;
    int new_y = t.x[1] * b.x + t.y[1] * b.y + t.z[1] * b.z;
    int new_z = t.x[2] * b.x + t.y[2] * b.y + t.z[2] * b.z;

    dx = new_x - a.x;
    dy = new_y - a.y;
    dz = new_z - a.z;
}

bool find_12_or_more(vector<Coordinate> &a, vector<Coordinate> &b, Transformation &t, int dx, int dy, int dz) {

    int counter = 0;
    for(auto coor : b) {
        int new_x = t.x[0] * coor.x + t.y[0] * coor.y + t.z[0] * coor.z;
        int new_y = t.x[1] * coor.x + t.y[1] * coor.y + t.z[1] * coor.z;
        int new_z = t.x[2] * coor.x + t.y[2] * coor.y + t.z[2] * coor.z;

        int x = new_x - dx;
        int y = new_y - dy;
        int z = new_z - dz;

        auto new_coor = Coordinate(x, y, z);
        for(auto target : a) {
            if (target.x != new_coor.x || target.y != new_coor.y || target.z != new_coor.z) continue;
            counter++;
            break;
        }
    }

    if (counter >= 12) {return true;}
    return false;
}

void find_equal(vector<Joiner> &joiner, vector<vector<Coordinate>> &scanners, int a, int b, vector<Transformation> &transform) {
    auto &first = scanners[a];
    auto &second = scanners[b];
    for(int i = 0 ; i < first.size() ; ++i)
        for(int j = 0 ; j < second.size() ; ++j) {
            for(auto t : transform) {
                int dx, dy, dz;
                get_deltas(dx, dy, dz, first[i], second[j], t);
                if (find_12_or_more(first, second, t, dx, dy, dz)) {
                    joiner.push_back(Joiner(a, b, dx, dy, dz, t));
                    return;
                }
            }
        }
}

vector<Transformation> generate_transforms() {

    vector<Transformation> ret;
    for(int p1 : {1, -1})
        for(int p2 : {1, -1})
            for(int c1 : {0, 1, 2})
                for(int c2 : {0, 1, 2}) {
                    if (c2 == c1) continue;
                    vector<int> x = {0, 0, 0};
                    vector<int> y = {0, 0, 0};
                    vector<int> z = {0, 0, 0};
                    x[c1] = p1;
                    y[c2] = p2;
                    z[0] = x[1] * y[2] - x[2] * y[1];
                    z[1] = -x[0] * y[2] + x[2] * y[0];
                    z[2] = x[0] * y[1] - x[1] * y[0];
                    ret.push_back(Transformation(x, y, z));
                }
    return ret;
}

int parent(vector<int> &clusters, int child) {

    if (clusters[child] == child) return child;

    clusters[child] = parent(clusters, clusters[child]);

    return clusters[child];
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");

    vector<vector<Coordinate>> scanners;
    while(true) {
        int scanner;
        if (fscanf(f, "%*s %*s %d %*s", &scanner) == EOF) break;
        vector<Coordinate> tmp;
        while(true) {
            int x, y, z;
            int count = fscanf(f, "%d,%d,%d", &x, &y, &z);
            if (count < 3) break;
            tmp.push_back(Coordinate(x, y, z));
        }
        scanners.push_back(tmp);
    }

    fclose(f);

    auto transformations = generate_transforms();

    vector<Joiner> joiners;
    for(int i = 0 ; i < scanners.size() ; ++i) {
        for(int j = 0 ; j < scanners.size() ; ++j) {
            if (i == j) continue;
            find_equal(joiners, scanners, i, j, transformations);
        }
    }

    map<int, set<tuple<int, int, int>>> count_all;

    for(int i = 0 ; i < scanners.size() ; ++i) {
        set<tuple<int, int, int>> coors;
        for(int j = 0 ; j < scanners[i].size() ; ++j){
            coors.insert({scanners[i][j].x, scanners[i][j].y, scanners[i][j].z});
        }
        count_all[i] = coors;
    }

    map<pair<int, int>, Joiner> transform_map;
    for(int i = 0 ; i < joiners.size() ; ++i) {
        transform_map[make_pair(joiners[i].first, joiners[i].second)] = joiners[i];
    }

    vector<int> clusters;
    for(int i = 0 ; i < scanners.size() ; ++i) {
        clusters.push_back(i);
    }

    while(true) {
        bool next = false;
        for(const auto &item : transform_map) {
            int to = item.first.first;
            int from = item.first.second;
            Joiner joiner = item.second;

            int parent_from = parent(clusters, from);
            clusters[parent_from] = parent(clusters, clusters[to]);

            int old_size = count_all[to].size();
            Transformation &t = joiner.t;
            for(const auto &coor : count_all[from]) {
                auto [ coor_x, coor_y, coor_z ] = coor;
                int new_x = t.x[0] * coor_x + t.y[0] * coor_y + t.z[0] * coor_z;
                int new_y = t.x[1] * coor_x + t.y[1] * coor_y + t.z[1] * coor_z;
                int new_z = t.x[2] * coor_x + t.y[2] * coor_y + t.z[2] * coor_z;

                int x = new_x - joiner.dx;
                int y = new_y - joiner.dy;
                int z = new_z - joiner.dz;

                count_all[to].insert({x, y, z});
            }
            next |= count_all[to].size() > old_size;
        }
        if (next == false) break;
    }

    set<int> visited;
    for(int i = 0 ; i < clusters.size() ; ++i) {
        int p = parent(clusters, i);
        visited.insert(p);
    }

    int sum = 0;
    for(auto p : visited) {
        cout << p << " " << count_all[p].size() << endl;
        sum += count_all[p].size();
    }

    cout << sum << endl;

    return 0;
}
