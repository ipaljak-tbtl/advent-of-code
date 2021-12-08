#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <map>
#include <set>

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

bool contains_all(const string &must_be_in, const string &parent) {
    for(auto c : must_be_in) {
        if (parent.find(c) == string::npos) return false;
    }
    return true;
}

bool deducted(const map<int, string> mapping, int num) {
    return mapping.find(num) != mapping.end();
}

int get_number(const vector<string> &measure, const vector<string> &display) {
    map<string, int> str_to_int;
    map<int, string> int_to_str;

    for(const auto& check : measure) {
        if (check.size() == 2) {int_to_str[1] = check; str_to_int[check] = 1;}
        else if (check.size() == 4) {int_to_str[4] = check; str_to_int[check] = 4;}
        else if (check.size() == 3) {int_to_str[7] = check; str_to_int[check] = 7;}
        else if (check.size() == 7) {int_to_str[8] = check; str_to_int[check] = 8;}
    }

    while(int_to_str.size() < 10) {
        for(const auto& check : measure) {
            if (str_to_int.find(check) != str_to_int.end()) continue;
            else if (check.size() == 5 && contains_all(int_to_str[1], check)) {int_to_str[3] = check; str_to_int[check] = 3;}
            else if (check.size() == 6 && contains_all(int_to_str[4], check)) {int_to_str[9] = check; str_to_int[check] = 9;}
            else if (check.size() == 6 && deducted(int_to_str, 9) && contains_all(int_to_str[7], check)) {int_to_str[0] = check; str_to_int[check] = 0;}
            else if (check.size() == 6 && deducted(int_to_str, 0) && deducted(int_to_str, 9)) {int_to_str[6] = check; str_to_int[check] = 6;}
            else if (check.size() == 5 && deducted(int_to_str, 3) && deducted(int_to_str, 9) && contains_all(check, int_to_str[9])) {int_to_str[5] = check; str_to_int[check] = 5;}
            else if (check.size() == 5 && deducted(int_to_str, 3) && deducted(int_to_str, 5)) {int_to_str[2] = check; str_to_int[check] = 2;}
        }
    }

    int base = 1000;
    int num = 0;
    for(const auto& check : display) {
        num += base * str_to_int[check];
        base /= 10;
    }

    return num;
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
        counter += get_number(measure, display);
        measure.clear();
        display.clear();
    }
    fclose(f);

    printf("%d\n", counter);

    return 0;
}
