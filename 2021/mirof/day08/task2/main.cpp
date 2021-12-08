#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<algorithm>

using namespace std;

string get_1(vector<string>& digital_numbers) {
    for(string number: digital_numbers)
        if(number.length() == 2)
            return number;

    cout << "ERR1" << endl;
    exit(1);
}

string get_4(vector<string>& digital_numbers) {
    for(string number: digital_numbers)
        if(number.length() == 4)
            return number;

    cout << "ERR4" << endl;
    exit(1);
}

string get_7(vector<string>& digital_numbers) {
    for(string number: digital_numbers)
        if(number.length() == 3)
            return number;

    cout << "ERR7" << endl;
    exit(1);
}

string get_8(vector<string>& digital_numbers) {
    for(string number: digital_numbers)
        if(number.length() == 7)
            return number;

    cout << "ERR8" << endl;
    exit(1);
}

string get_9(vector<string>& digital_numbers) {
    string dig_4 = get_4(digital_numbers);

    for(string number: digital_numbers) {
        string intersection;
        std::set_intersection(
            number.begin(), number.end(),
            dig_4.begin(), dig_4.end(),
            std::back_inserter(intersection)
        );

        if(number.length() == 6 && intersection == dig_4)
            return number;
    }

    cout << "ERR9" << endl;
    exit(1);
}

string get_3(vector<string>& digital_numbers) {
    string dig_7 = get_7(digital_numbers);

    for(string number: digital_numbers) {
        string intersection;
        std::set_intersection(
            number.begin(), number.end(),
            dig_7.begin(), dig_7.end(),
            std::back_inserter(intersection)
        );

        if(number.length() == 5 && intersection == dig_7)
            return number;
    }

    cout << "ERR3" << endl;
    exit(1);
}

string get_0(vector<string>& digital_numbers) {
    string dig_1 = get_1(digital_numbers);
    string dig_9 = get_9(digital_numbers);

    for(string number: digital_numbers) {
        string intersection;
        std::set_intersection(
            number.begin(), number.end(),
            dig_1.begin(), dig_1.end(),
            std::back_inserter(intersection)
        );

        if(number.length() == 6 && number != dig_9 && intersection == dig_1)
            return number;
    }

    cout << "ERR0" << endl;
    exit(1);
}

string get_6(vector<string>& digital_numbers) {
    string dig_0 = get_0(digital_numbers);
    string dig_9 = get_9(digital_numbers);

    for(string number: digital_numbers)
        if(number.length() == 6 && number != dig_0 && number != dig_9)
            return number;

    cout << "ERR6" << endl;
    exit(1);
}

string get_5(vector<string>& digital_numbers) {
    string dig_6 = get_6(digital_numbers);

    for(string number: digital_numbers) {
        string intersection;
        std::set_intersection(
            number.begin(), number.end(),
            dig_6.begin(), dig_6.end(),
            std::back_inserter(intersection)
        );

        if(number.length() == 5 && intersection == number)
            return number;
    }

    cout << "ERR5" << endl;
    exit(1);
}

string get_2(vector<string>& digital_numbers) {
    string dig_3 = get_3(digital_numbers);
    string dig_5 = get_5(digital_numbers);

    for(string number: digital_numbers)
        if(number.length() == 5 && number != dig_3 && number != dig_5)
            return number;

    cout << "ERR2" << endl;
    exit(1);
}

int get_number(vector<string>& digital_numbers, string digital_number) {
    if(get_0(digital_numbers) == digital_number) return 0;
    if(get_1(digital_numbers) == digital_number) return 1;
    if(get_2(digital_numbers) == digital_number) return 2;
    if(get_3(digital_numbers) == digital_number) return 3;
    if(get_4(digital_numbers) == digital_number) return 4;
    if(get_5(digital_numbers) == digital_number) return 5;
    if(get_6(digital_numbers) == digital_number) return 6;
    if(get_7(digital_numbers) == digital_number) return 7;
    if(get_8(digital_numbers) == digital_number) return 8;
    if(get_9(digital_numbers) == digital_number) return 9;

    exit(1);
}

int sum_right_sides() {
    ifstream infile("../input.txt");
    string word;
    int result = 0;
    int input_size = 200;
    char empty;

    for(int i = 0; i < input_size; i++) {
        vector<string> left_side;
        for(int j = 0; j < 10; j++) {
            infile >> word;
            sort(word.begin(), word.end());
            left_side.push_back(word);
        }

        infile >> word;

        int pow = 1000;
        int number = 0;
        for(int j = 0; j < 4; j++) {
            infile >> word;
            sort(word.begin(), word.end());

            int decimal = get_number(left_side, word);
            number += pow * decimal;
            pow /= 10;
        }

        result += number;
    }

    return result;
}

int main() {
    cout << sum_right_sides() << endl;

    return 0;
}
