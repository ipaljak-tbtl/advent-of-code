#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>

using namespace std;

#define SIZE 16

#define lld long long int

void fill_me_up(char *input, vector<lld> *output) {
    lld size = strlen(input);
    lld base = 1;
    lld number = 0;
    for(lld i = size - 1; i >= 0 ; --i) {
        if (input[i] == ',') {output->push_back(number);base=1;number=0;continue;}
        number += base * (input[i] - '0');
        base *= 10;
    }
    output->push_back(number);

    reverse(output->begin(), output->end());
}

void mul_matrix(const vector<vector<lld>> &A, const vector<vector<lld>> &B, vector<vector<lld>> *C) {

    for(size_t i = 0 ; i < SIZE ; ++i)
        for(size_t j = 0 ; j < SIZE ; ++j) {
            lld sum = 0;
            for(size_t k = 0 ; k < SIZE ; ++k) sum += A[i][k]*B[k][j];
            (*C)[i][j] = sum;
        }
}

void pow_matrix(const vector<vector<lld>> &A, lld pow, vector<vector<lld>> *C) {
    // I don't care about 0, no time for that :D
    if (pow == 1) {
        *C = A;
        return;
    }

    if (pow % 2 == 0) {
        auto tmp = A;
        pow_matrix(A, pow / 2, &tmp);
        mul_matrix(tmp, tmp, C);
        return;
    }
    else {
        auto tmp = A;
        pow_matrix(A, pow / 2, &tmp);
        auto mid = A;
        mul_matrix(tmp, tmp, &mid);
        mul_matrix(A, mid, C);
    }

}

vector<lld> mul_vector(const vector<lld> &A, const vector<vector<lld>> &B) {
    auto ret = A;
    for(size_t i = 0 ; i < SIZE ; ++i) {
        lld sum = 0;
        for(size_t k = 0 ; k < SIZE ; ++k) sum += A[k]*B[k][i];
        ret[i] = sum;
    }
    return ret;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    lld days = atoi(argv[2]);
    FILE *f = fopen(argv[1], "r");
    char buff[1000];
    fscanf(f, "%s", buff);
    fclose(f);

    vector<lld> input;
    fill_me_up(buff, &input);

    vector<lld> init_vector(SIZE);
    for(auto count : input) init_vector[count]++;

    vector<vector<lld>> matrix_mania = {
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    };

    auto M = matrix_mania;
    pow_matrix(matrix_mania, days, &M);

    auto solution = mul_vector(init_vector, M);

    lld count = 0;
    for(auto i : solution) count += i;
    printf("%lld\n", count);

    return 0;
}
