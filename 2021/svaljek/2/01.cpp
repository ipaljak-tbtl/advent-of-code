#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string command;
    ifstream input{"./input.txt"};
    int amount{0}, distance{0}, depth{0};

    while (input >> command >> amount) {
        if (command == "forward")
            distance += amount;
        else if (command == "up")
            depth -= amount;
        else if (command == "down")
            depth += amount;
    }

    cout << "Depth: " << depth << endl;
    cout << "Distance: " << distance << endl;
}
