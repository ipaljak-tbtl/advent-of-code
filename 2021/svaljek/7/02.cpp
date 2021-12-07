#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream input{"./input.txt"};
    vector<int> crabs;
    int crab;
    char comma;

    input >> crab;
    crabs.push_back(crab);
    while (input >> comma >> crab)
        crabs.push_back(crab);

    sort(crabs.begin(), crabs.end());

    int min_fuel{INT_LEAST32_MAX};
    int min_position = crabs[0];
    for (int i = crabs[0]; i <= crabs[crabs.size()-1]; i++) {
        int fuel{0};
        for (auto crab: crabs) {
            int steps = abs(crab - i);
            for (int i = 1; i <= steps; i++) {
                fuel += i;
            }
        }
        if (fuel < min_fuel) {
            min_position = i;
            min_fuel = fuel;
        }
    }

    cout << min_fuel << endl;
}
