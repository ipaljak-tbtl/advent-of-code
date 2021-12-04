#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

struct Matrix {

    vector<bool> matrix;
    vector<int> number_index;

    Matrix(const vector<int> &table) {
        for(int i = 0 ; i < 25 ; ++i) matrix.push_back(false);
        for(int i = 0 ; i < 101 ; ++i) number_index.push_back(-1);
        for(int i = 0 ; i < table.size() ; ++i) number_index[table.at(i)] = i;
    }

    void add_number(int num) {
        int index = number_index.at(num);
        if (index == -1) return;
        matrix[index] = true;
    }

    bool is_over() {
        for(int i = 0 ; i < 5 ; ++i) {
            bool all_true = true;
            for(int j = 0 ; j < 5 ; ++j) {
                if (matrix.at(i*5+j) == false) {all_true=false;break;}
            }
            if (all_true) return true;
        }
        for(int i = 0 ; i < 5 ; ++i) {
            bool all_true = true;
            for(int j = 0 ; j < 5 ; ++j) {
                if (matrix.at(j*5+i) == false) {all_true=false;break;}
            }
            if (all_true) return true;
        }
        return false;
    }

};

struct MatrixSet {
    vector<Matrix> all;
    set<int> game_over = set<int>();
    int winner_index = -1;

    MatrixSet(const vector<vector<int>> tables) {
        for(int i = 0 ; i < tables.size() ; ++i) all.push_back(Matrix(tables.at(i)));
    }

    void add_number(int num) {
        for(int i = 0 ; i < all.size() ; ++i) {
            if (game_over.find(i) != game_over.end()) continue;
            all.at(i).add_number(num);
            if (all.at(i).is_over()) {
                winner_index = i;
                game_over.insert(i);
            }
        }
    }
};

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

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    vector<int> number_list;
    char buff[1000];

    FILE *f = fopen(argv[1], "r");

    fscanf(f, "%s", buff);
    fill_me_up(buff, &number_list);

    int number;
    vector<vector<int>> all_tables;
    vector<int> table;
    while(fscanf(f, "%d", &number) != EOF) {
        table.push_back(number);
        if (table.size() == 25) {all_tables.push_back(table);table.clear();}
    }
    fclose(f);

    auto bingo = MatrixSet(all_tables);

    int last_number;
    bool checked[101] = {0};
    for(int i = 0 ; i < number_list.size() ; ++i) {
        bingo.add_number(number_list.at(i));
        checked[number_list.at(i)] = true;
        if (bingo.game_over.size() == all_tables.size()) {last_number = number_list.at(i); break;}
    }

    auto end_table = all_tables.at(bingo.winner_index);
    int sum = 0;

    for(int i = 0 ; i < end_table.size() ; ++i) {
        if (checked[end_table.at(i)] == false) sum += end_table.at(i);
    }

    printf("%d %d %d\n", last_number, sum, bingo.winner_index);
    printf("%d\n", last_number * sum);

    return 0;
}
