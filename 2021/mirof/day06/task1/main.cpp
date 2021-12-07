#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>

using namespace std;

vector<int> parse_fishes() {
    ifstream infile("../input.txt");
    string fishes;
    vector<int> result;

    infile >> fishes;
    stringstream stream(fishes);

    while(stream.good()) {
        string substr;
        getline(stream, substr, ',');
        result.push_back(stoi(substr));
    }

    return result;
}

int count(int fish, int day) {
    if(day == 0) return 1;
    else if(fish == 0) return count(6, day-1) + count(8, day-1);
    else return count(fish - 1, day - 1);
}

int main() {
    vector<int> fishes = parse_fishes();
    array<int, 5> memo{0};
    int days = 80;
    int result = 0;

    for(int fish: fishes) {
        if(memo[fish]) result += fish;
        else result += count(fish, days);
    }

    cout << result;

    return 0;
}
