#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main() {
    std::ifstream infile("../input.txt");

    string command;
    int value;

    int x_position = 0;
    int y_position = 0;
    int aim = 0;

    while (infile >> command >> value) {
        switch (command [0]) {
            case 'f': x_position += value; y_position += aim * value; break;
            case 'u': aim -= value; break;
            case 'd': aim += value; break;
            default:  exit(1);
        }
    }

    cout << x_position * y_position;

    return 0;
}
