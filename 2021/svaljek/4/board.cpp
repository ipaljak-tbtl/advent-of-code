#include "board.h"

void Board::add(int number) {
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
            if (m[x][y].first == number)
                m[x][y].second = true;
}

int Board::score(int number) {
    int sum{0};
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
            if (!m[x][y].second)
                sum += m[x][y].first;

    return number*sum;
}

bool Board::bingo() {
    if (won) return false;

    for (int x = 0; x < 5; x++) {
        int count{0};
        for (int y = 0; y < 5; y++)
            if (m[x][y].second) count++;
        if (count == 5) {
            won = true;
            return true;
        }
    }

    for (int y = 0; y < 5; y++) {
        int count{0};
        for (int x = 0; x < 5; x++)
            if (m[x][y].second) count++;
        if (count == 5) {
            won = true;
            return true;
        }
    }

    return false;
}
