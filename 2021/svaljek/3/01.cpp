#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string number;
    int stats[12] = {0};
    ifstream input{"./input.txt"};


    while (input >> number)
        for (int i = 0; i < 12; i++)
            stats[i] += 2 * (number[i] - '0') - 1;


    unsigned gamma{0}, epsilon{};
    for (int i = 0; i < 12; i++) {
        gamma *= 2;
        epsilon *= 2;
        if (stats[i] > 0)
            gamma += 1;
        else
            epsilon += 1;

    }

    cout << "Gamma: " << gamma << endl;
    cout << "Epsilon: " << epsilon << endl;
}
