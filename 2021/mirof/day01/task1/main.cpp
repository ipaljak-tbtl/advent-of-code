#include<iostream>

int main() {
    int last_number, number, counter = 0;

    std::cin >> last_number;

    while(std::cin >> number) {
        counter += number > last_number;
        last_number = number;
    }

    std::cout << counter;

    return 0;
}
