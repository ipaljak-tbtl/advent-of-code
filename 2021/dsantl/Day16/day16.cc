#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <queue>

using namespace std;


struct Package {

    short version;
    short typeID;
    vector<short> digits;
    short lengthID;
    short length;

    vector<Package> packages;
    bool stop = false;
};

struct State {

    FILE *f;
    short bit_pnt = -1;
    short current_num = 0;
    int counter = 0;
    bool stop = false;

    State(FILE *f) {
        this->f = f;
    }

    short get_next_bit() {
        if (stop == true) return -1;
        if (bit_pnt < 0) {
            char buff;
            fscanf(f, "%c", &buff);
            if (buff == '\n') {stop = true; return -1;}
            current_num = buff - '0';
            if (current_num > 9) current_num = 10 + buff - 'A';
            bit_pnt = 3;
        }

        int ret = (current_num >> bit_pnt) & 1;
        bit_pnt--;
        counter++;
        // cout << ret;
        return ret;
    }

    Package process_package(bool padding_control = true) {

        Package package;

        package.version = (get_next_bit() << 2) | (get_next_bit() << 1) | get_next_bit();
        package.typeID = (get_next_bit() << 2) | (get_next_bit() << 1) | get_next_bit();

        if (stop) {
            package.stop = true;
            return package;
        }

        cout << "Version typeID " << package.version << " " << package.typeID << endl;

        if (package.typeID == 4) {
            while(true) {
                short stop_flag = get_next_bit();
                short digit_part =  (get_next_bit() << 3) | (get_next_bit() << 2) | (get_next_bit() << 1) | get_next_bit();
                package.digits.push_back(digit_part);
                if (!stop_flag) break;
            }
        }
        else {
            package.lengthID = get_next_bit();
            if (package.lengthID == 0) {
                package.length = 0;
                for(int i = 0 ; i < 15 ; ++i) {
                    package.length <<= 1;
                    package.length |= get_next_bit();
                }
                cout << "BIT COUNTER: " << package.length << endl;
                int current_bits = counter;
                while(counter < current_bits + package.length) {
                    if (stop == true) break; // TODO
                    Package child = process_package(false);
                    package.packages.push_back(child);
                }
            }
            else {
                package.length = 0;
                for(int i = 0 ; i < 11 ; ++i) {
                    package.length <<= 1;
                    package.length |= get_next_bit();
                }
                cout << "ELEMENT COUNTER: " << package.length << endl;
                for(int i = 0 ; i < package.length ; ++i) {
                    Package child = process_package();
                    package.packages.push_back(child);
                }
            }
        }

        return package;
    }

};

int version_sum(const vector<Package> &packages) {
    int sum = 0;
    for(int i = 0 ; i < packages.size() ; ++i) {
        if (packages[i].stop) continue;
        sum += packages[i].version;
        sum += version_sum(packages[i].packages);
    }
    return sum;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\e[31mDummy dummy!\n\e[0m");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    State state(f);
    vector<Package> packages;
    while(true) {
        Package package = state.process_package();
        packages.push_back(package);
        if (state.stop) break;
    }
    fclose(f);

    cout << version_sum(packages) << endl;

    return 0;
}
