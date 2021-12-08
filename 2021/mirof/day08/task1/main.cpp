#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<algorithm>

using namespace std;

int count_unique_digits() {
    ifstream infile("../input.txt");
    string word;
    int result = 0;
    int input_size = 200;
    char empty;

    for(int i = 0; i < input_size; i++) {
        while(infile >> empty)
            if(empty == '|')
                break;

        for(int j = 0; j < 4; j++) {
            infile >> word;
            result += word.length() == 2;
            result += word.length() == 4;
            result += word.length() == 3;
            result += word.length() == 7;
        }
    }

    return result;
}

int main() {
    cout << count_unique_digits() << endl;

    return 0;
}
