#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Point {
    int x1, y1;
    int x2, y2;

    Point(int x1, int y1, int x2, int y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");

    vector<Point> points;
    int index = 0, x1, y1, x2, y2;
    int max_x = 0;
    int max_y = 0;
    while(fscanf(f, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
        if (x1 == x2 || y1 == y2) {
            Point point = Point(x1, y1, x2, y2);
            max_x = max(max_x, x1); max_x = max(max_x, x2);
            max_y = max(max_y, y1); max_y = max(max_y, y2);
            points.push_back(point);
        }
    }
    fclose(f);

    bool touch[1000][1000] = {0};
    int board[1000][1000] = {0};
    for(const auto &point : points) {
        for(int i = min(point.x1, point.x2) ; i <= max(point.x1, point.x2) ; ++i) touch[i][point.y1] = true;
        for(int i = min(point.y1, point.y2) ; i <= max(point.y1, point.y2) ; ++i) touch[point.x1][i] = true;
        for(int i = min(point.x1, point.x2) ; i <= max(point.x1, point.x2) ; ++i)
            for(int j = min(point.y1, point.y2) ; j <= max(point.y1, point.y2) ; ++j)
                if (touch[i][j]) board[i][j]++;
    }

    int counter = 0;
    for(int i = 0 ; i <= max_x ; ++i)
        for(int j = 0 ; j <= max_y ; ++j)
            if (board[i][j] >= 2) counter++;

    printf("%d\n", counter);
    return 0;
}
