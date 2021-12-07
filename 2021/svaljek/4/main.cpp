#include <fstream>
#include <iostream>
#include "loaders.h"
using namespace std;

int main() {
    ifstream input{"./input.txt"};
    auto numbers = load_random(input);
    auto tables = load_tables(input);

    for (auto number: numbers)
        for (auto& table: tables) {
            table.add(number);
            if (table.bingo()) cout << table.score(number) << endl;
        }

}
