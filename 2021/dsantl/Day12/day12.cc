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

void fill_me_up(char *buff, string &a, string &b) {

    a = "";
    b = "";

    int size = strlen(buff);

    bool to_app = false;
    for(int i = 0 ; i < size ; ++i) {
        if (buff[i] == '-') {to_app = true; continue;}
        if (to_app) b += buff[i];
        else a += buff[i];
    }

}

int count_paths(map<string, vector<string>> &graph) {

    int count = 0;
    stack<State> stack;
    stack.push(State("start", 0));
    set<string> forbidden;

    while(!stack.empty()) {
        State top = stack.top();
        stack.pop();

        if (top.node == "end") {count++; continue;}
        if (top.next_index == graph[top.node].size()) {forbidden.erase(top.node); continue;}

        stack.push(State(top.node, top.next_index + 1));

        if (islower(top.node[0])) forbidden.insert(top.node);

        int i = top.next_index;
        string next_one = graph[top.node].at(i);
        if (forbidden.find(next_one) != forbidden.end()) continue;

        stack.push(State(next_one, 0));
    }

    return count;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    map<string, vector<string>> graph;

    FILE *f = fopen(argv[1], "r");
    char buff[100];
    string a;
    string b;

    while(fscanf(f, "%s", buff) != EOF) {
        fill_me_up(buff, a, b);
        if (graph.find(a) == graph.end()) graph[a] = {};
        if (graph.find(b) == graph.end()) graph[b] = {};
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    fclose(f);

    int sol = count_paths(graph);

    cout << sol << endl;

    return 0;
}
