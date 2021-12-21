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

using namespace std;

bool sim(int vx, int vy, int x1, int x2, int y1, int y2) {

    int x = 0;
    int y = 0;

    while(true) {
        x += vx;
        y += vy;

        vx = max(vx - 1, 0);
        vy -= 1;

        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) return true;

        if (y < y1) return false;
    }

}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    int x1, x2, y1, y2;
    FILE *f = fopen(argv[1], "r");
    fscanf(f, "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);
    fclose(f);

    int count = 0;
    int min_v_x = (-1 + sqrt(1 + 2 * x1)) / 2;
    int max_v_x = x2;

    int min_v_y = y1;
    int max_v_y = -y1;

    for(int x = min_v_x ; x <= max_v_x ; ++x)
        for(int y = min_v_y ; y <= max_v_y ; ++y)
            if (sim(x, y, x1, x2, y1, y2))
                count++;

    cout << count << endl;

    return 0;
}
