#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main() {
    std::ifstream infile("../input.txt");

    int line_length = 12;
    int mask = 4095;

    int counter[line_length] = {0};
    int file_length = 0;

    char character;
    int index = 0;

    while(infile.get(character)) {
        if(character == '\n') { index = 0; continue; }
        else if(character == '1') counter[index] += 1;

        index++;
        file_length++;
    }

    file_length /= line_length;

    int result = 0;
    for(int i = 0; i < line_length; i++) {
        bool decimal = counter[i] > (file_length / 2);
        result |= decimal << (line_length - i - 1);
    }

    cout << (result * (result ^ mask)) << endl;

    return 0;
}
