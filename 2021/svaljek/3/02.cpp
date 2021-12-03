#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int value(const string& line) {
    int value{0};
    for (int i = 0; i < 12; i++) {
        value *= 2;
        value += line[i] - '0';
    }
    return value;
}

int chew(const vector<string>& numbers, unsigned position, bool less) {
    if (numbers.size() == 1) return value(numbers[0]);

    int stat{0};
    for (auto const& number: numbers)
        stat += 2 * (number[position] - '0') - 1;

    stat = !signbit(stat);
    if (less) stat = !stat;

    vector<string> next;
    for (auto const& number: numbers)
        if (number[position] == '0' + stat)
            next.push_back(number);

    return chew(next, position + 1, less);
}

int main() {
    string number;
    ifstream input{"./input.txt"};

    vector<string> numbers;
    while (input >> number)
        numbers.push_back(number);

    cout << "Oxygen generator rating: " << chew(numbers, 0, true) << endl;
    cout << "CO2 scrubber rating: " << chew(numbers, 0, false) << endl;
}
