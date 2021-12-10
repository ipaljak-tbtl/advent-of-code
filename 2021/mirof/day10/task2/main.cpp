#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<algorithm>

using namespace std;

vector<string> parse_lines() {
    ifstream infile("../input.txt");
    string line;
    vector<string> result;

    while(infile >> line)
        result.push_back(line);

    return result;
}

pair<bool, vector<char>> find_stack(string line) {
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

            return make_pair(false, stack);
        }
    }

    return make_pair(true, stack);
}

int main() {
    vector<string> lines = parse_lines();
    vector<long> results;

    for(auto line: lines) {
        auto entry = find_stack(line);

        if(entry.first) {
            long r = 0L;
            vector<char> l = entry.second;

            while(l.size() != 0) {
                r *= 5L;
                char top_char = l[l.size() - 1];
                l.pop_back();

                if(top_char == '(') r += 1L;
                if(top_char == '[') r += 2L;
                if(top_char == '{') r += 3L;
                if(top_char == '<') r += 4L;

            }

            results.push_back(r);
        }
    }

    sort(results.begin(), results.end());

    printf("%ld", results[results.size() / 2]);

    return 0;
}
