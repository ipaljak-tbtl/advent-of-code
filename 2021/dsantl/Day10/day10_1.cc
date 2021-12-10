#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>

using namespace std;

const int A = 1;
const int B = 2;
const int C = 3;
const int D = 4;

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

long long int get_invalid_score(const vector<int> &input) {
    stack<int> stack;
    int size = input.size();
    for(int i = 0 ; i < size ; ++i) {
        if (input[i] < 0) {stack.push(input[i]); continue;}
        int top = stack.top();
        stack.pop();
        if (top + input[i] != 0) return -1;
    }

    long long int ret = 0;
    while(!stack.empty()) {
        int top = stack.top();
        ret = ret*5 - top;
        stack.pop();
    }

    return ret;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    char buff[10000];
    long long int score;
    vector<long long int> scores;
    while(fgets(buff, 10000, f) != NULL) {
        vector<int> input;
        fill_me_up(buff, &input);
        score = get_invalid_score(input);
        if (score != -1) scores.push_back(score);
    }
    fclose(f);

    sort(scores.begin(), scores.end());

    cout << scores[scores.size() / 2] << endl;

    return 0;
}
