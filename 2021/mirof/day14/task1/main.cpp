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

    while(infile >> pair >> ignore >> new_elem) {
        rules.insert({pair, new_elem});
    }

    return rules;
}

string step(string polymer, map<string, char>& rules) {
    string result_polymer{};

    for(int i = 0; i < polymer.length() - 1; i++) {
        string pair;
        pair += polymer[i];
        pair += polymer[i+1];
        char new_elem = rules.find(pair)->second;

        result_polymer += polymer[i];
        result_polymer += new_elem;
    }

    result_polymer += polymer[polymer.length() - 1];
    return result_polymer;
}

long sub_most_and_least_frequent_chars(string polymer) {
    array<int, 30> freqs{};
    for(char c: polymer)
        freqs[c - 'A']++;

    long min = 9999999999;
    long max = 0;

    for(int freq: freqs) {
        if(freq != 0 && min > freq) min = freq;
        if(freq > max) max = freq;
    }

    cout << "MIN: " << min << endl;
    cout << "MAX: " << max << endl;

    return max - min;
}

int main() {
    ifstream infile("../input.txt");
    string polymer = parse_polymer(infile);
    map<string, char> rules = parse_rules(infile);

    for(int i = 0; i < 10; i++) {
        polymer = step(polymer, rules);
        cout << "Iteration: " << i << endl;
        int result = sub_most_and_least_frequent_chars(polymer);

        cout << "Result " << i << ": " << result << endl;
    }

    return 0;
}
