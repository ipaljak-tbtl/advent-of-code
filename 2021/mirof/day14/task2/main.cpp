#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<map>

using namespace std;

string parse_polymer(ifstream& infile) {
    string polymer, ignore;

    infile >> polymer;

    return polymer;
}

map<string, char> parse_rules(ifstream& infile) {
    map<string, char> rules{};
    string pair, ignore;
    char new_elem;

    while(infile >> pair >> ignore >> new_elem)
        rules.insert({pair, new_elem});


    return rules;
}

long long count_character(
        char first,
        char second,
        char target,
        int depth,
        bool count_second,
        map<pair<pair<string, int>, bool>, long long>& counter,
        map<string, char> const& rules
) {
    if(depth == 0) {
      if(count_second) return second == target;
      return 0;
    }

    string key;
    key += first;
    key += second;

    if(counter.find({{key, depth}, count_second}) != counter.end()) return counter.find({{key, depth}, count_second})->second;

    long long count = count_second && (second == target);
    char next = rules.find(key)->second;
    count += count_character(first, next,   target, depth - 1, true, counter, rules);
    count += count_character(next,  second, target, depth - 1, false, counter, rules);

    counter.insert({{{key, depth}, count_second}, count});

    return count;
}

int main() {
    ifstream infile("../input.txt");
    string polymer = parse_polymer(infile);
    map<string, char> rules = parse_rules(infile);
    int depth = 40;
    long long min = 999999999999999999;
    long long max = 0;

    for(char target = 'A'; target <= 'Z'; target++) {
        long long count = 0;
        map<pair<pair<string, int>, bool>, long long> counter;

        int i = 0;
        for(i = 0; i < polymer.length() - 1; i++) {
            count += count_character(polymer[i], polymer[i+1], target, depth, 0, counter, rules);
            count += polymer[i] == target;
        }
        count += polymer[i] == target;

        if(count > max) max = count;
        if(count != 0 && count < min) min = count;
    }

    cout << max - min << endl;

    return 0;
}
