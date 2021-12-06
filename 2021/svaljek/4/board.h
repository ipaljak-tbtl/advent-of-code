#pragma once
#include <array>
#include <tuple>

class Board {
public:
    using Cell = std::pair<int, bool>;
    using Matrix = std::array<std::array<Cell, 5>, 5>;

    Board(Matrix m) : m{m} {}

    bool bingo();
    void add(int number);
    int score(int number);

private:
    bool won{false};
    Matrix m;
};
