#include <fstream>
#include <iostream>
#include "map.h"
using namespace std;

int main() {
    char c;
    int x1, y1, x2, y2;
    ifstream input{"./input.txt"};

    Map map;
    while (input >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2) {

        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            for (int i = y1; i <= y2; i++)
                map.add(x1, i);
        }

        else if (y1 == y2) {
            if (x1 > x2) swap(x1, x2);
            for (int i = x1; i <= x2; i++)
                map.add(i, y1);

        }
    }

    cout << map.count() << endl;
}
