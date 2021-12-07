#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>

using namespace std;

void fill_me_up(char *input, vector<int> *output) {
    int size = strlen(input);
    int base = 1;
    int number = 0;
    for(int i = size - 1; i >= 0 ; --i) {
        if (input[i] == ',') {output->push_back(number);base=1;number=0;continue;}
        number += base * (input[i] - '0');
        base *= 10;
    }
    output->push_back(number);

    reverse(output->begin(), output->end());
}

int calc_fuel(const vector<int> data, int x) {
    int fuel = 0;
    for(auto num : data) fuel += abs(num - x) * (abs(num - x) + 1) / 2;
    return fuel;
}

int main(int argc, char** argv) {

    std::srand(time(nullptr));

    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[10000];
    fscanf(f, "%s", buff);
    fclose(f);

    vector<int> input;
    fill_me_up(buff, &input);

    int total = 0;
    for(auto num : input) total += num;

    int avg = total / input.size();

    int min = calc_fuel(input, avg);
    bool next = true;
    int iter = 1;
    while(next) {
        next = false;
        int min1 = calc_fuel(input, avg + iter);
        int min2 = calc_fuel(input, avg - iter);
        if (min1 < min) {min = min1; next = true;}
        if (min2 < min) {min = min2; next = true;}
        ++iter;
    }

    printf("%d\n", min);

    return 0;
}
