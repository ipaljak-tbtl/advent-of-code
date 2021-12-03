#include <iostream>

using namespace std;

int main(void) {

    int a, b, c, d;
    int before;
    int count = 0;

    FILE *f = fopen("test.txt", "r");

    fscanf(f, "%d", &a);
    fscanf(f, "%d", &b);
    fscanf(f, "%d", &c);

    before = a + b + c;

    while(fscanf(f, "%d", &d) != EOF) {
        if (d > a) ++count;
        a = b;
        b = c;
        c = d;
    }

    fclose(f);

    printf("%d\n", count);

    return 0;
}
