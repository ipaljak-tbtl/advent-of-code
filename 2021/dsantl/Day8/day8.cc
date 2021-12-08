#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>

using namespace std;

void fill_me_up(char *input, vector<string> &measure, vector<string> &display) {
    int size = strlen(input);
    bool display_mode = false;
    string tmp;
    for(int i = 0 ; i < size ; ++i) {
        if (input[i] == '|') {i += 1; display_mode = true; continue;}
        else if (input[i] == ' ' || input[i] == '\n') {
            sort(tmp.begin(), tmp.end());
            if (display_mode) display.push_back(tmp);
            else measure.push_back(tmp);
            tmp = "";
        }
        else tmp += input[i];
    }
}

int easy_count(const vector<string> &display) {
    int counter = 0;
    for(const auto& check : display) {
        if (check.size() == 2) counter++; // 1
        else if (check.size() == 4) counter++; // 4
        else if (check.size() == 3) counter++; // 7
        else if (check.size() == 7) counter++; // 8
    }
    return counter;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[10000];
    vector<string> measure;
    vector<string> display;
    int counter = 0;
    while(fgets(buff, 10000, f) != NULL) {
        fill_me_up(buff, measure, display);
        counter += easy_count(display);
        measure.clear();
        display.clear();
    }
    fclose(f);

    printf("%d\n", counter);

    return 0;
}
