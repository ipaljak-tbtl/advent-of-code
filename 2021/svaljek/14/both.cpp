#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <map>
#define fn auto
using namespace std;
using Rules = map<pair<char, char>, char>;
using Edges = map<pair<char, char>, uint64_t>;
using Stats = map<char, uint64_t>;

fn get_edges(ifstream& input) -> pair<Edges, string> {
    Edges edges;
    string text;
    input >> text;
    for (int i = 0; i < text.size() - 1; i++)
        edges[make_pair(text[i], text[i+1])]++;
    return make_pair(edges, text);
}

fn get_rules(ifstream& input) -> Rules {
    Rules rules;
    char a, b, c, x;
    while (input >> a >> b >> x >> x >> c)
        rules[make_pair(a, b)] = c;
    return rules;
}

fn update(Edges& edges, const Rules& rules) -> Edges {
    Edges result;
    for (const auto& rule: rules) {
        auto edge = edges.find(rule.first);
        if (edge != edges.end()) {
            auto count = edge->second;
            edges.erase(edge);
            result[make_pair(rule.first.first, rule.second)] += count;
            result[make_pair(rule.second, rule.first.second)] += count;
        }
    }
    for (auto edge: edges)
        result[edge.first] += edge.second;
    return result;
}

fn calculate(const Edges& edges, char first, char last) -> uint64_t {
    Stats stats;
    for (const auto& edge: edges) {
        stats[edge.first.first] += edge.second;
        stats[edge.first.second] += edge.second;
    }
    stats[first]++;
    stats[last]++;
    for (auto& stat: stats)
        stat.second /= 2;

    uint64_t max{0};
    uint64_t min{UINT_LEAST64_MAX};
    for (auto stat: stats) {
        if (stat.second < min)
            min = stat.second;
        if (stat.second > max)
            max = stat.second;
    }
    return max - min;
}

constexpr int STEPS{40}; // or 40

fn main() -> int {
    ifstream input{"./input.txt"};
    auto poly = get_edges(input);
    auto rules = get_rules(input);

    auto first = *(poly.second.begin());
    auto last = *(--poly.second.end());

    auto edges = poly.first;
    for (int i = 0; i < STEPS; i++)
        edges = update(edges, rules);

    cout << calculate(edges, first, last) << endl;
}
