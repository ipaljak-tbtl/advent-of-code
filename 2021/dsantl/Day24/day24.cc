#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <sstream>

using namespace std;

struct Memory {
    int w = 0, x = 0, y = 0, z = 0;

    void set_value(string m, int value) {
        if (m == "w") w = value;
        else if (m == "x") x = value;
        else if (m == "y") y = value;
        else if (m == "z") z = value;
        else throw -1;
    }

    int get_value(string m) {
        if (m == "w") return w;
        if (m == "x") return x;
        if (m == "y") return y;
        if (m == "z") return z;
        return atoi(m.c_str());
    }

    void print() {
        cout << "w=" << w;
        cout << " x=" << x;
        cout << " y=" << y;
        cout << " z=" << z;
        cout << endl;
    }

};

struct Command {
    string command;
    string opr1;
    string opr2;

    Command(string command, string opr1, string opr2) {
        this->command = command;
        this->opr1 = opr1;
        this->opr2 = opr2;
    }

    Command(string command, string opr1) {
        this->command = command;
        this->opr1 = opr1;
    }
};

struct Input {

    string input;
    int curr = 0;

    Input(string input) {
        this->input = input;
    }

    int next() {
        if (this->curr == input.size()) throw -1;
        return input[this->curr++] - '0';
    }

};

Command parse_command(FILE *f, string comm) {
    if (comm == "inp") {
        char buff[20];
        fscanf(f, "%s", buff);
        return Command(comm, buff);
    }
    char buff1[20], buff2[20];
    fscanf(f, "%s %s", buff1, buff2);
    return Command(comm, buff1, buff2);
}

void execute_command(Command command, Memory &m, Input &input) {
    if (command.command == "inp") {
        m.set_value(command.opr1, input.next());
        return;
    }
    if (command.command == "add") {
        int new_value = m.get_value(command.opr1) + m.get_value(command.opr2);
        m.set_value(command.opr1, new_value);
        return;
    }
    if (command.command == "mul") {
        int new_value = m.get_value(command.opr1) * m.get_value(command.opr2);
        m.set_value(command.opr1, new_value);
        return;
    }
    if (command.command == "div") {
        int new_value = m.get_value(command.opr1) / m.get_value(command.opr2);
        m.set_value(command.opr1, new_value);
        return;
    }
    if (command.command == "mod") {
        int new_value = m.get_value(command.opr1) % m.get_value(command.opr2);
        m.set_value(command.opr1, new_value);
        return;
    }
    if (command.command == "eql") {
        int new_value = m.get_value(command.opr1) == m.get_value(command.opr2) ? 1 : 0;
        m.set_value(command.opr1, new_value);
        return;
    }
    throw -1;
}

int simulate(const vector<Command> &commands, int w, int z) {
    stringstream ss;
    ss << w;
    Memory memory;
    memory.set_value("z", z);
    Input input = Input(ss.str());
    for(const auto &com : commands) {
        execute_command(com, memory, input);
    }
    return memory.get_value("z");
}

int simulate(const vector<vector<Command>> &commands, string in) {
    Memory memory;
    Input input = Input(in);
    for(int i = 0 ; i < in.size() ; ++i) {
        for(const auto &com : commands[i]) {
            execute_command(com, memory, input);
        }
    }
    return memory.get_value("z");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    vector<vector<Command>> commands;
    vector<Command> tmp;

    FILE *f = fopen(argv[1], "r");
    char buff[20];
    while(fscanf(f, "%s", buff) != EOF) {
        Command command = parse_command(f, buff);
        if (command.command == "inp" && !tmp.empty()) {
            commands.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(command);
    }
    commands.push_back(tmp);
    fclose(f);

    map<int, string> z_mem;
    for(int i = 1 ; i <= 9 ; ++i) {
        stringstream ss;
        ss << i;
        bool invalid = false;
        for(auto c : ss.str()) if (c == '0') invalid = true;
        if (invalid) continue;
        int new_z = simulate(commands, ss.str());
        if (z_mem.find(new_z) != z_mem.end()) continue;
        z_mem[new_z] = ss.str();
    }

    for(int k = 0 ; k < 9 ; ++k) {
        map<int, string> z_mem_1;
        for(const auto &item : z_mem) {
            for(int i = 1 ; i <= 9 ; ++i) {
                stringstream ss;
                ss << item.second << i;
                bool invalid = false;
                for(auto c : ss.str()) if (c == '0') invalid = true;
                if (invalid) continue;
                int new_z = simulate(commands, ss.str());
                if (z_mem_1.find(new_z) != z_mem_1.end()) continue;
                z_mem_1[new_z] = ss.str();
            }
        }
        z_mem = z_mem_1;
    }

    for(const auto &item : z_mem) {
        for(int i = 9999 ; i >= 1111 ; --i) {
            stringstream ss;
            ss << item.second << i;
            bool invalid = false;
            for(auto c : ss.str()) if (c == '0') invalid = true;
            if (invalid) continue;
            int new_z = simulate(commands, ss.str());
            if (new_z == 0) {cout << ss.str() << endl;}
        }
    }

    return 0;
}
