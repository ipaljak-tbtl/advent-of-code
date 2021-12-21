#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <cmath>
#include <tuple>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    int players[2];

    FILE *f = fopen(argv[1], "r");
    fscanf(f, "Player 1 starting position: %d\n", &players[0]);
    fscanf(f, "Player 2 starting position: %d\n", &players[1]);
    fclose(f);

    const int DICE_SIZE = 100;
    const int TABLE_SIZE = 10;

    long long int score[2] = {0, 0};
    int turn = 0;
    int dice = 1;
    int count = 0;

    while(true) {
        cout << count << " " << players[0] << " " << players[1] << endl;
        count += 1;
        int step = ((dice++) + (dice++) + (dice++) - 1) % DICE_SIZE + 1;
        int position = (players[turn] + step - 1) % TABLE_SIZE + 1;
        cout << step << " " << position << endl;
        players[turn] = position;
        score[turn] += position;
        if (score[turn] >= 1000) break;
        dice = (dice - 1) % DICE_SIZE + 1;
        turn = (turn + 1) % 2;
    }

    int mini = min(score[0], score[1]);

    cout << mini << " " << count << endl;
    cout << 3 * mini * count << endl;

    return 0;
}
