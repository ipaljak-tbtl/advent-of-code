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

using namespace std;

void fill_me_up(char *line, vector<char> *input) {
    int size = strlen(line) - 1;
    for(int i = 0 ; i < size ; ++i) input->push_back(line[i]);
}

void print(const vector<vector<char>> &m) {
     for(int i = 0 ; i < m.size() ; ++i) {
        for(int j = 0 ; j < m[i].size() ; ++j) {
            cout << m[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void find_final_space(const vector<vector<char>> &m, map<char, int> *final) {
    set<int> spaces;
     //for(int i = 0 ; i < m.size() ; ++i) {
        for(int j = 0 ; j < m[2].size() ; ++j) {
            if (m[2][j] != '#') spaces.insert(j);
            //if (m[i][j] >= 'A' && m[i][j] <= 'Z') spaces.insert(j);
        }
    //}
    char begin = 'A';
    for(auto col : spaces) {
        (*final)[begin++] = col;
    }
}

bool check_game_end(const vector<vector<char>> &m, const map<char, int> &final) {
    for(int i = 0 ; i < m.size() ; ++i) {
        for(int j = 0 ; j < m[i].size() ; ++j) {
            if (m[i][j] >= 'A' && m[i][j] <= 'Z') {
                if (final.at(m[i][j]) != j) return false;
            }
        }
    }
    return true;
}

int calc_cost(const pair<int, int> &final, int i, int j, char sign) {
    int cost = pow(10, sign - 'A');
    return cost;
}

void fill_positions(const vector<vector<char>> &m, int i, int j, const map<char, int> &final, vector<pair<int, pair<int, int>>> &positions) {

    if (final.at(m[i][j]) == j) {
        bool check = true;
        for(int k = i + 1 ; k < m.size() ; ++k) {
            if (m[k][j] == '#') break;
            if (m[k][j] != m[i][j]) {check = false; break;}
        }
        if (check) return;
    }

    queue<pair<int, pair<int, int>>> q;
    q.push(make_pair(0, make_pair(i, j)));

    set<pair<int, int>> visited;

    while(!q.empty()) {
        auto top_all = q.front();
        auto top = top_all.second;
        auto distance = top_all.first;
        q.pop();

        if (visited.find(top) != visited.end()) continue;
        visited.insert(top);

        for(int delta : {-1, 1}) {
            if (top.first + delta < 0 || top.first + delta >= m.size() || m[top.first + delta][top.second] != '.') {}
            else q.push(make_pair(distance + 1, make_pair(top.first + delta, top.second)));

            if (top.second + delta < 0 || top.second + delta >= m[top.first].size() || m[top.first][top.second + delta] != '.') continue;
            else q.push(make_pair(distance + 1, make_pair(top.first, top.second + delta)));
        }

        if (i == top.first && j == top.second) continue;
        if (top.first == 1 && m[top.first + 1][top.second] != '#') continue;
        if (top.first > 1 && top.second != final.at(m[i][j])) continue;
        if (top.first == 1 && i == 1) continue;
        if (i == 1 && top.second != final.at(m[i][j])) continue;
        if (top.first > 1 && m[top.first + 1][top.second] != '#' && m[top.first + 1][top.second] != m[i][j]) continue;

        if (top.first > 1) {
            bool check = false;
            for(int k = top.first + 1 ; k < m.size() ; ++k) {
                if (m[k][top.second] == '#') break;
                if (m[k][top.second] != m[i][j]) {check = true; break;}
            }
            if (check) continue;
        }

        positions.push_back(top_all);
    }

}

void find_new_states(const vector<vector<char>> &m, vector<pair<int, vector<vector<char>>>> &new_states, const map<char, int> &final) {
    for(int i = 0 ; i < m.size() ; ++i) {
        for(int j = 0 ; j < m[i].size() ; ++j) {
            if (m[i][j] >= 'A' && m[i][j] <= 'Z') {
                vector<pair<int, pair<int, int>>> positions;
                fill_positions(m, i, j, final, positions);
                for(const auto &all : positions) {
                    const auto &item = all.second;
                    auto distance = all.first;
                    int cost = distance * calc_cost(item, i, j, m[i][j]);
                    auto new_map = m;
                    new_map[item.first][item.second] = m[i][j];
                    new_map[i][j] = '.';
                    new_states.push_back(make_pair(cost, new_map));
                }
            }
        }
    }
}

int find_solution(const vector<vector<char>> &m, const map<char, int> &final) {
    priority_queue<pair<int, vector<vector<char>>>> q;
    q.push(make_pair(0, m));

    set<vector<vector<char>>> visited;
    set<vector<vector<char>>> open;

    while(!q.empty()) {

        auto top = q.top();
        q.pop();

        const auto &state = top.second;
        auto cost = top.first;

        if (visited.find(state) != visited.end()) continue;
        visited.insert(state);

        cout << cost << endl;

        if (check_game_end(state, final)) {
            //print_sol(state);
            //cout << costeri[state] << endl;
            print(state);
            return -cost;
        }

        vector<pair<int, vector<vector<char>>>> new_states;

        find_new_states(state, new_states, final);

        for(const auto &new_state : new_states) {
            if (visited.find(new_state.second) != visited.end()) continue;
            q.push(make_pair(cost - new_state.first, new_state.second));
            // cout << "STATE " << cost << endl;
            // print(state);
            // cout << "NEIGH" << (cost - new_state.first) << endl;
            // print(new_state.second);
        }
    }

    return -1;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    vector<vector<char>> m;
    char buff[10000];
    while(fgets(buff, 10000, f) != NULL) {
        vector<char> input;
        fill_me_up(buff, &input);
        m.push_back(input);
    }
    fclose(f);

    map<char, int> final_space;
    find_final_space(m, &final_space);

    int sol = find_solution(m, final_space);

    cout << sol << endl;

    return 0;
}
