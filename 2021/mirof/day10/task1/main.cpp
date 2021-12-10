#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>

using namespace std;

vector<string> parse_lines() {
    ifstream infile("../input.txt");
    string line;
    vector<string> result;

    while(infile >> line)
        result.push_back(line);

    return result;
}

char find_error_char(string line) {
    vector<char> stack{};

    for(char c: line) {
        if(c == '<' || c == '(' || c == '[' || c == '{') stack.push_back(c);
        else {
            char top_char =  stack[stack.size() - 1];
            stack.pop_back();

            if((top_char == '<' && c == '>') ||
               (top_char == '(' && c == ')') ||
               (top_char == '[' && c == ']') ||
               (top_char == '{' && c == '}')
              ) continue;

            return c;
        }
    }

    return -1;
}

int main() {
    vector<string> lines = parse_lines();
    int result = 0;

    for(auto const& line: lines) {
        char error = find_error_char(line);

        if(error == -1) continue;

        if(error == '>') result += 25137;
        if(error == ')') result += 3;
        if(error == ']') result += 57;
        if(error == '}') result += 1197;
    }

    cout << result << endl;

    return 0;
}
