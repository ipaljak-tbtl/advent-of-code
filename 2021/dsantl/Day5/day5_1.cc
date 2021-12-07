#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Line {
    int x1, y1;
    int x2, y2;

    Line(int x1, int y1, int x2, int y2) {
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

    vector<Line> simple_points;
    vector<Line> complex_points;
    int index = 0, x1, y1, x2, y2;
    int max_x = 0;
    int max_y = 0;
    while(fscanf(f, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
        max_x = max(max_x, x1); max_x = max(max_x, x2);
        max_y = max(max_y, y1); max_y = max(max_y, y2);
        Line line = Line(x1, y1, x2, y2);
        if (x1 == x2 || y1 == y2) simple_points.push_back(line);
        else complex_points.push_back(line);
    }
    fclose(f);

    int board[1000][1000] = {0};
    for(const auto &point : simple_points) {
        for(int i = min(point.x1, point.x2) ; i <= max(point.x1, point.x2) ; ++i)
            for(int j = min(point.y1, point.y2) ; j <= max(point.y1, point.y2) ; ++j)
                board[i][j]++;
    }

    for(const auto &point : complex_points) {
        int steps = abs(point.x1 - point.x2) + 1;
        int dx = point.x1 - point.x2; if (dx > 0) dx = 1; else if (dx < 0) dx = -1;
        int dy = point.y1 - point.y2; if (dy > 0) dy = 1; else if (dy < 0) dy = -1;
        for(int i = 0 ; i < steps ; ++i)
            board[point.x2 + dx*i][point.y2 + dy*i]++;
    }

    int counter = 0;
    for(int i = 0 ; i <= max_x ; ++i)
        for(int j = 0 ; j <= max_y ; ++j)
            if (board[i][j] >= 2) counter++;

    printf("%d\n", counter);
    return 0;
}
