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

struct Volume {
    int time;
    bool on;
    int x1, x2;
    int y1, y2;
    int z1, z2;
};

struct Event {
    int value;
    bool begin;
    int index;
};

bool by_value(const Event &a, const Event &b) { return a.value < b.value; }


void remove_event(Event &e, vector<Event> &open) {
    for(int i = 0 ; i < open.size() ; ++i) {
        if (e.index != open[i].index) continue;
        open.erase(open.begin() + i);
        break;
    }
}

Event find_bigest_open_event(vector<Event> &open, const vector<Volume> &input, bool &check) {
    int max_time = -1;
    Event ret;
    for(int i = 0 ; i < open.size() ; ++i) {
        if (max_time > input[open[i].index].time) continue;
        max_time = input[open[i].index].time;
        ret = open[i];
    }

    check = true;
    if (max_time == -1) check = false;

    return ret;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    vector<Volume> input;
    int index = 0;
    char buff[100];
    FILE *f = fopen(argv[1], "r");
    while(fscanf(f, "%s", buff) != EOF) {
        bool on = buff[1] == 'n';
        int x1, x2, y1, y2, z1, z2;
        fscanf(f, " x=%d..%d,y=%d..%d,z=%d..%d\n", &x1, &x2, &y1, &y2, &z1, &z2);
        // if (x1 < -50 || x2 > 50 || y1 < -50 || y2 > 50 || z1 < -50 || z2 > 50) continue;
        input.push_back({index++, on, x1, x2, y1, y2, z1, z2});
    }
    fclose(f);

    vector<Event> x_events;
    vector<Event> y_events;
    vector<Event> z_events;

    for(int i = 0 ; i < input.size() ; ++i) {
        Volume &vol = input[i];
        x_events.push_back({vol.x1, true, i});
        x_events.push_back({vol.x2 + 1, false, i});

        y_events.push_back({vol.y1, true, i});
        y_events.push_back({vol.y2 + 1, false, i});

        z_events.push_back({vol.z1, true, i});
        z_events.push_back({vol.z2 + 1, false, i});
    }

    sort(x_events.begin(), x_events.end(), by_value);
    sort(y_events.begin(), y_events.end(), by_value);
    sort(z_events.begin(), z_events.end(), by_value);

    vector<int> x_points;
    vector<int> y_points;
    vector<int> z_points;

    for(const auto &e : x_events) {
        if (x_points.empty() || x_points.back() != e.value) x_points.push_back(e.value);
    }

    for(const auto &e : y_events) {
        if (y_points.empty() || y_points.back() != e.value) y_points.push_back(e.value);
    }

    for(const auto &e : z_events) {
        if (z_points.empty() || z_points.back() != e.value) z_points.push_back(e.value);
    }

    long long int total_count = 0;
    for(int k = 0 ; k < z_points.size() - 1 ; ++k) {
        cout << k << " " << z_points.size() << endl;
        long long int count_z = 0;
        for(int j = 0 ; j < y_points.size() - 1 ; ++j) {
            long long int count_y = 0;
            vector<vector<Event>> events;
            for(Event e : x_events) {
                if (y_points[j] < input[e.index].y1 || y_points[j] > input[e.index].y2) continue;
                if (z_points[k] < input[e.index].z1 || z_points[k] > input[e.index].z2) continue;
                if (events.empty() || events.back().back().value != e.value) events.push_back({});
                events.back().push_back(e);
            }

            vector<Event> open;
            for(int i = 0 ; i < events.size() ; ++i) {

                for(int w = 0 ; w < events[i].size() ; ++w) {
                    Event &e = events[i][w];
                    if (i != 0 && w == 0) {
                        bool check;
                        Event big_event = find_bigest_open_event(open, input, check);
                        if (check && input[big_event.index].on) {
                            count_y += e.value - events[i - 1][0].value;
                        }
                    }
                    if (e.begin) open.push_back(e);
                    else remove_event(e, open);
                }

            }
            count_z += count_y * (y_points[j + 1] - y_points[j]);
        }
        total_count += count_z * (z_points[k + 1] - z_points[k]);
    }

    cout << total_count << endl;

    return 0;
}
