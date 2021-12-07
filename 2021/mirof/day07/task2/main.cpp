#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<algorithm>

using namespace std;

vector<int> parse_crabs() {
    ifstream infile("../input.txt");
    vector<int> result;
    int crab;
    char comma;

    while(infile >> crab >> comma)
        result.push_back(crab);

    infile >> crab;
    result.push_back(crab);

    return result;
}

int calculate_fuel(vector<int> &crabs, int position) {
    int needed_fuel = 0;
    for(int crab: crabs) {
        int position_change = abs(position - crab);
        needed_fuel += position_change * (position_change + 1) / 2;
    }
    return needed_fuel;
}

int main() {
    vector<int> crabs = parse_crabs();

    int min = *min_element(crabs.begin(), crabs.end());
    int max = *max_element(crabs.begin(), crabs.end());

    int min_fuel = calculate_fuel(crabs, min);

    for(int pos = min + 1; pos <= max; pos++) {
        int needed_fuel = calculate_fuel(crabs, pos);
        if(min_fuel > needed_fuel) min_fuel = needed_fuel;
    }

    cout << min_fuel << endl;

    return 0;
}
