#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string command;
    ifstream input{"./input.txt"};
    int amount{0}, distance{0}, depth{0}, aim{0};

    while (input >> command >> amount) {
        if (command == "forward") {
            distance += amount;
            depth += aim*amount;
        }
        else if (command == "up")
            aim -= amount;
        else if (command == "down")
            aim += amount;
    }

    cout << "Depth: " << depth << endl;
    cout << "Distance: " << distance << endl;
}
