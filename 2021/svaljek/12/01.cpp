#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#define fn auto

using namespace std;
class Cave {
    bool m_small;
    string m_name;
public:
    Cave(string name) : m_small{(bool)islower(name[0])}, m_name{move(name)} {}
    fn operator<(const Cave& other) const -> bool { return this->m_name < other.m_name; }
    fn name() const -> const string& { return m_name; }
    fn small() const -> bool { return m_small; }
};

using Map = map<Cave, vector<Cave>>;
using Paths = set<string>;
using Visited = map<Cave, uint64_t>;

fn get_map() -> Map {
    Map map;
    ifstream input{"./input.txt"};
    string path;

    while (input >> path) {
        auto pos = path.find('-');
        auto first = path.substr(0, pos);
        auto second = path.substr(pos+1);
        map[first].push_back(second);
        map[second].push_back(first);
    }

    return map;
}

fn add_paths(const Cave& current, Map& map, string path, Paths& paths, Visited visited_small) {
    if (current.name() == "end") {
        paths.insert(path);
        return;
    }

    if (current.name() == "start" && path != "start") return;

    if (current.small()) {
        if (visited_small[current] < 1) {
            visited_small[current]++;
        } else {
            return;
        }
    }

    for (auto const& cave : map[current])
        add_paths(cave, map, path + "," + cave.name(), paths, visited_small);
}

fn main() -> int {
    auto map = get_map();
    Visited visited_small;
    Paths paths;

    add_paths(Cave{"start"}, map, string("start"), paths, visited_small);
    cout << paths.size() << endl;
}
