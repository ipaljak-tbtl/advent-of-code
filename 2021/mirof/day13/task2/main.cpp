#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<set>

using namespace std;

set<pair<int, int>> parse_coordinates(ifstream& infile) {
    set<pair<int, int>> coordinates;

    int x, y;
    char ignore_char;
    while(infile >> x >> ignore_char >> y)
        coordinates.insert(make_pair(y, x));

    return coordinates;
}

vector<pair<char, int>> parse_queries(ifstream& infile, int ignore_lines) {
    vector<pair<char, int>> queries;

    char ignore_char, coordinate;
    string ignore_string;
    int value;
    while(ignore_lines--) infile >> ignore_string;
    while(infile >> ignore_string >> ignore_string >> coordinate >> ignore_char >> value)
       queries.push_back(make_pair(coordinate, value));

    return queries;
}

set<pair<int, int>> fold(pair<char, int> query, set<pair<int, int>> coordinates) {
    set<pair<int, int>> new_set;

    if(query.first == 'y') {
        for(auto coordinate: coordinates) {
            if(coordinate.first > query.second) {
                int diff = coordinate.first - query.second;
                new_set.insert(make_pair((coordinate.first - 2 * diff), coordinate.second));
            }
            else
                new_set.insert(coordinate);
        }
    }

    if(query.first == 'x') {
        for(auto coordinate: coordinates) {
            if(coordinate.second > query.second) {
                int diff = coordinate.second - query.second;
                new_set.insert(make_pair(coordinate.first, (coordinate.second - 2 * diff)));
            }
            else
                new_set.insert(coordinate);
        }
    }

    return new_set;
}

int main() {
    ifstream infile1("../input.txt");
    set<pair<int, int>> coordinates = parse_coordinates(infile1);
    ifstream infile2("../input.txt");
    vector<pair<char, int>> queries = parse_queries(infile2, coordinates.size());

    for(auto query: queries) {
        coordinates = fold(query, coordinates);
    }

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 40; j++) {
            if(coordinates.find(make_pair(i, j)) != coordinates.end()) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }

    return 0;
}
