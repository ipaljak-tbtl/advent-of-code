#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>

using namespace std;

const int A = 3;
const int B = 57;
const int C = 1197;
const int D = 25137;

void fill_me_up(char *line, vector<int> *input) {

    int size = strlen(line) - 1;
    for(int i = 0 ; i < size ; ++i) {
        if (line[i] == '(') input->push_back(-A);
        if (line[i] == '[') input->push_back(-B);
        if (line[i] == '{') input->push_back(-C);
        if (line[i] == '<') input->push_back(-D);
        if (line[i] == ')') input->push_back(A);
        if (line[i] == ']') input->push_back(B);
        if (line[i] == '}') input->push_back(C);
        if (line[i] == '>') input->push_back(D);
    }
}

int get_invalid_score(char *buff, const vector<int> &input) {
    stack<int> stack;
    int size = input.size();
    for(int i = 0 ; i < size ; ++i) {
        if (input[i] < 0) {stack.push(input[i]); continue;}
        int top = stack.top();
        stack.pop();
        if (top + input[i] != 0) return input[i];
    }
    return 0;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[10000];
    int counter = 0;
    while(fgets(buff, 10000, f) != NULL) {
        vector<int> input;
        fill_me_up(buff, &input);
        counter += get_invalid_score(buff, input);
    }
    fclose(f);

    printf("%d\n", counter);

    return 0;
}
