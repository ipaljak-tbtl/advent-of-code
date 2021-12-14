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

    string old = init;
    stringstream ss;
    stringstream pattern;

    for(int step = 0 ; step < 10 ; ++step) {
        for(int i = 0 ; i < old.size() - 1; ++i) {
            ss << old[i];
            pattern << old.at(i) << old.at(i + 1);

            string patern_str = pattern.str();
            if (rules.find(patern_str) != rules.end()) {
                ss << rules[patern_str];
            }

            pattern.str("");
        }
        ss << old[old.size() - 1];

        old = ss.str();
        ss.str("");
    }

    int counter[50] = {0};
    for(int i = 0 ; i < old.size() ; ++i) {
        counter[old[i] - 'A']++;
    }

    int min = old.size();
    int max = 0;

    for(int i = 0 ; i <= 'Z' - 'A' ; ++i) {
        if (counter[i] > max) max = counter[i];
        if (counter[i] < min && counter[i] != 0) min = counter[i];
    }

    cout << min << endl;
    cout << max << endl;
    cout << max - min << endl;

    return 0;
}
