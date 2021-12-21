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


struct Pair {

    bool regular = true;
    int number;

    Pair* l_a = nullptr;
    Pair* l_b = nullptr;
    Pair* parent = nullptr;

    Pair(Pair *p, int number) {
        this->number = number;
        this->parent = p;
        regular = true;
    }

    Pair(Pair *p) {
        regular = false;
        this->parent = p;
    }

};

void print_pair(Pair *pair) {

    if (pair == nullptr) {cout << "NULL" << endl; return;}

    if (pair->regular) {cout << pair->number; return;}

    cout << "[";
    print_pair(pair->l_a);
    cout << ",";
    print_pair(pair->l_b);
    cout << "]";

}

Pair* generate_pair(Pair* p, const char *line, int start, int end) {

    if (start == end) {
        return new Pair(p, line[start] - '0');
    }

    int counter = 0;
    int split;

    for(int i = start ; i <= end ; ++i) {
        if (line[i] == '[') counter++;
        if (line[i] == ']') counter--;
        if (counter == 1 && line[i] == ',') {split = i; break;}
    }

    Pair *current = new Pair(p);

    Pair *a = generate_pair(current, line, start + 1, split - 1);
    Pair *b = generate_pair(current, line, split + 1, end - 1);

    current->l_a = a;
    current->l_b = b;

    return current;
}

Pair *find_left(Pair *curr) {

    if (curr->parent->l_b == curr) curr = curr->parent->l_a;
    else {
        while(curr != nullptr) {
            if (curr->parent == nullptr || curr->parent->l_a == curr) curr = curr->parent;
            else break;
        }
        if (curr == nullptr) return nullptr;
        curr = curr->parent->l_a;
    }

    while(!curr->regular) {
        curr = curr->l_b;
    }

    return curr;
}

Pair *find_right(Pair *curr) {

    if (curr->parent->l_a == curr) curr = curr->parent->l_b;
    else {
        while(curr != nullptr) {
            if (curr->parent == nullptr || curr->parent->l_b == curr) curr = curr->parent;
            else break;
        }
        if (curr == nullptr) return nullptr;
        curr = curr->parent->l_b;
    }

    while(!curr->regular) {
        curr = curr->l_a;
    }

    return curr;
}

bool explode(Pair *pair, int depth = 1) {

    if (pair->regular) return false;

    if (depth == 5) {

        Pair *left = find_left(pair);
        Pair *right = find_right(pair);

        if (left != nullptr) left->number += pair->l_a->number;
        if (right != nullptr) right->number += pair->l_b->number;

        pair->regular = true;
        pair->number = 0;

        delete pair->l_a;
        delete pair->l_b;

        pair->l_a = nullptr;
        pair->l_b = nullptr;

        return true;
    }

    if (explode(pair->l_a, depth + 1)) return true;
    if (explode(pair->l_b, depth + 1)) return true;

    return false;
}

bool splits(Pair *pair) {

    if (pair->regular) {
        if (pair->number >= 10) {
            int down = floor(pair->number / 2.0);
            int up = ceil(pair->number / 2.0);
            Pair *a = new Pair(pair, down);
            Pair *b = new Pair(pair, up);
            pair->regular = false;
            pair->l_a = a;
            pair->l_b = b;
            return true;
        }
        return false;
    }

    if (splits(pair->l_a)) return true;
    if (splits(pair->l_b)) return true;

    return false;
}

void reduce(Pair *pair) {
    while(true) {
        if (explode(pair)) {print_pair(pair); cout << endl; continue;}
        if (splits(pair))  {print_pair(pair); cout << endl; continue;}
        break;
    }
}

long long int magnitute(Pair *pair) {
    if (pair->regular) return pair->number;
    return 3 * magnitute(pair->l_a) + 2 * magnitute(pair->l_b);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[100];
    fscanf(f, "%s", buff);
    Pair *first = generate_pair(nullptr, buff, 0, strlen(buff) - 1);

    print_pair(first); cout << endl;

    while(fscanf(f, "%s", buff) != EOF) {
        Pair *parent = new Pair(nullptr);
        Pair *second = generate_pair(parent, buff, 0, strlen(buff) - 1);
        first->parent = parent;
        parent->l_a = first;
        parent->l_b = second;
        first = parent;
        reduce(first);
    }
    fclose(f);

    print_pair(first); cout << endl;

    cout << magnitute(first) << endl;

    return 0;
}
