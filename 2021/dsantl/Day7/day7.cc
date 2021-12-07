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

void quick_sort(vector<int> &data, int lo, int hi) {
    if (hi - lo <= 1) return;

    int pivot = lo + rand() % (hi - lo);
    swap(data[lo], data[pivot]);
    pivot = lo;

    int future_pivot = lo + 1;
    int current = lo + 1;

    while(current < hi) {
        if (data[current] < data[pivot]) {
            swap(data[current], data[future_pivot]);
            future_pivot++;
        }
        current++;
    }
    swap(data[pivot], data[future_pivot - 1]);

    quick_sort(data, lo, future_pivot - 1);
    quick_sort(data, future_pivot, hi);
}


int kth(vector<int> &data, int k, int lo, int hi) {
    if (hi - lo <= 1) return data[lo];

    int pivot = lo + rand() % (hi - lo);
    swap(data[lo], data[pivot]);
    pivot = lo;

    int future_pivot = lo + 1;
    int current = lo + 1;

    while(current < hi) {
        if (data[current] < data[pivot]) {
            swap(data[current], data[future_pivot]);
            future_pivot++;
        }
        current++;
    }
    future_pivot = future_pivot - 1;

    swap(data[pivot], data[future_pivot]);

    if (future_pivot > k) return kth(data, k, lo, future_pivot);
    else if (future_pivot < k) return kth(data, k, future_pivot + 1, hi);
    else return data[future_pivot];
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

    // quick_sort(input, 0, input.size());
    // int median = input.at(input.size() / 2);

    int median = kth(input, input.size() / 2, 0, input.size());

    int fuel = 0;
    for(auto num : input) fuel += abs(num - median);

    printf("%d\n", fuel);

    return 0;
}
