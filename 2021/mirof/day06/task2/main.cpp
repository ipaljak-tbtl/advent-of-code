#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<map>

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

std::map<pair<int,int>, long> count_memo;

long count(int fish, int day) {
    if(day <= 0) return 1;

    else if(fish == 0) {
        if(count_memo.find(make_pair(fish, day)) != count_memo.end()) return count_memo[make_pair(fish, day)];
        long res = count(0, day-1-6) + count(0, day-1-8);
        count_memo[make_pair(fish, day)] = res;
        return res;
    }
    else return count(0, day - fish);
}

int main() {
    vector<int> fishes = parse_fishes();
    array<int, 5> memo{0};
    int days = 256;
    long result = 0;

    for(int fish: fishes) {
        if(memo[fish]) result += fish;
        else result += count(fish, days);
    }

    cout << result;

    return 0;
}
