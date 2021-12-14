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
#include <climits>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    map<string, char> rules;

    char init[100];
    char a[100];
    char b;
    FILE *f = fopen(argv[1], "r");
    fscanf(f, "%s", init);

    while(fscanf(f, "%s -> %c", a, &b) != EOF) {
        rules[a] = b;
    }
    fclose(f);


    long long int counter[50] = {0};

    map<string, long long int> state;

    stringstream ss;
    int size = strlen(init);

    for(int i = 0 ; i < size ; ++i) counter[init[i] - 'A']++;

    for(int i = 0 ; i < size - 1; ++i) {
        ss << init[i] << init[i + 1];
        string pattern = ss.str();
        if (state.find(pattern) == state.end()) state[pattern] = 0;
        state[pattern] += 1;
        ss.str("");
    }

    for(int step = 0 ; step < 40 ; ++step) {
        map<string, long long int> new_state;
        for(const auto &x : state) {
            if (rules.find(x.first) == rules.end()) {
                if (new_state.find(x.first) == new_state.end()) new_state[x.first] = 0;
                new_state[x.first] = x.second;
                continue;
            }

            char new_chr = rules[x.first];
            counter[new_chr - 'A'] += x.second;

            ss.str("");
            ss << x.first[0] << new_chr;
            if (new_state.find(ss.str()) == new_state.end()) new_state[ss.str()] = 0;
            new_state[ss.str()] += x.second;

            ss.str("");
            ss << new_chr << x.first[1];
            if (new_state.find(ss.str()) == new_state.end()) new_state[ss.str()] = 0;
            new_state[ss.str()] += x.second;
        }
        state = new_state;
    }

    long long int min = LLONG_MAX;
    long long int max = 0;
    for(int i = 0 ; i <= 'Z' - 'A' ; ++i) {
        cout << i << " " << counter[i] << endl;
        if (counter[i] > max) max = counter[i];
        if (counter[i] < min && counter[i] != 0) min = counter[i];
    }

    cout << min << endl;
    cout << max << endl;
    cout << max - min << endl;

    return 0;
}
