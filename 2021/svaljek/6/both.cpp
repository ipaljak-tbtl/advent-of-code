#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using BigInt = boost::multiprecision::int128_t;
using Map = unordered_map<int, BigInt>;

constexpr int DAYS{80}; // or 256

int main() {
    int fish;
    char comma;
    Map fishes;
    ifstream input{"./input.txt"};

    input >> fish;
    fishes[fish]++;
    while (input >> comma >> fish)
        fishes[fish]++;

    for (int day = 0; day < DAYS; day++) {
        BigInt zeroes = fishes[0];
        for (int n = 0; n < 8; n++)
            fishes[n] = fishes[n+1];
        fishes[6] += zeroes;
        fishes[8] = zeroes;
    }

    BigInt counter{0};
    for (auto& n: fishes) {
        counter += n.second;
    }
    cout << counter << endl;
}
