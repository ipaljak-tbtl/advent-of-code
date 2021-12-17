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

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    int x1, x2, y1, y2;
    FILE *f = fopen(argv[1], "r");
    fscanf(f, "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);
    fclose(f);

    cout << y1 * (y1 + 1) / 2 << endl;

    return 0;
}
