#include<iostream>

int main() {
    int first, second, third, forth, counter = 0;

    std::cin >> first;
    std::cin >> second;
    std::cin >> third;

    while(std::cin >> forth) {
        counter += (second + third + forth) > (first + second + third);

        first = second;
        second = third;
        third = forth;
    }

    std::cout << counter;

    return 0;
}
