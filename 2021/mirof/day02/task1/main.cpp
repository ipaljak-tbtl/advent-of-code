#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main() {
    std::ifstream infile("../input.txt");

    string direction;
    int value;

    int x_position = 0;
    int y_position = 0;

    while (infile >> direction >> value) {
        switch (direction[0]) {
            case 'f': x_position += value; break;
            case 'u': y_position -= value; break;
            case 'd': y_position += value; break;
            default:  exit(1);
        }
    }

    cout << x_position * y_position;

    return 0;
}
