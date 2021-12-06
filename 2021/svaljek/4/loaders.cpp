#include "board.h"
#include "loaders.h"
using namespace std;

vector<Board> load_tables(ifstream& input) {
    int number;
    vector<Board> tables;

    Board::Matrix matrix;
    while (true) {
        for (int x = 0; x < 5; x++)
            for (int y = 0; y < 5; y++) {
                if (!(input >> number)) return tables;
                matrix[x][y] = make_pair(number, false);
        }
        tables.push_back(matrix);
    }
}

vector<int> load_random(ifstream& input) {
    char comma;
    int number;
    vector<int> numbers;

    input >> number;
    numbers.push_back(number);
    input >> comma;

    while (true) {
        input >> number;
        numbers.push_back(number);
        if (input.peek() != ',') return numbers;
        input >> comma;
    }
}
