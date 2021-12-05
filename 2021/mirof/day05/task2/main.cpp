#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>
#include<algorithm>

using namespace std;

vector<array<int, 4>> parse_lines(ifstream &infile) {
    vector<array<int, 4>> lines{};
    char empty_char;
    string empty_string;

    for(int i = 0; i < 500; i++) {
        array<int, 4> line;
        infile >> line[0];
        infile >> empty_char;
        infile >> line[1];
        infile >> empty_string;
        infile >> line[2];
        infile >> empty_char;
        infile >> line[3];

        lines.push_back(line);
    }

    return lines;
}

array<array<int, 1000>, 1000> fill_matrix(vector<array<int, 4>> lines) {
    array<array<int, 1000>, 1000> matrix{0};

    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            matrix[i][j] = 0;
        }
    }

    for(auto const& line: lines) {
        if(line[0] == line[2]) {
            for(int i = line[1]; i <= line[3]; i++) {
                matrix[line[0]][i] += 1;
            }
            for(int i = line[3]; i <= line[1]; i++) {
                matrix[line[0]][i] += 1;
            }
        }
        else if(line[1] == line[3]) {
            for(int i = line[0]; i <= line[2]; i++) {
                matrix[i][line[1]] += 1;
            }
            for(int i = line[2]; i <= line[0]; i++) {
                matrix[i][line[1]] += 1;
            }
        } else if(abs(line[3] - line[1]) == abs(line[2] - line[0]))  {
            cout << line[0] << " " << line[1] << "-" << line[2] << " " << line[3] << endl;

            if(line[0] <= line[2] && line[1] <= line[3]) {
                for(int i = 0; i <= line[2] - line[0]; i++) {
                    matrix[line[0] + i][line[1] + i] += 1;
                }
                continue;
            }

            if(line[0] <= line[2] && line[1] >= line[3]) {
                for(int i = 0; i <= line[2] - line[0]; i++) {
                    matrix[line[0] + i][line[1] - i] += 1;
                }
                continue;
            }

            if(line[0] >= line[2] && line[1] >= line[3]) {
                for(int i = 0; i <= line[0] - line[2]; i++) {
                    matrix[line[0] - i][line[1] - i] += 1;
                }
                continue;
            }

            if(line[0] >= line[2] && line[1] <= line[3]) {
                for(int i = 0; i <= line[0] - line[2]; i++) {
                    matrix[line[0] - i][line[1] + i] += 1;
                }
                continue;
            }
        }
    }

    return matrix;
}

int count_greater_than_one_fields(array<array<int, 1000>, 1000> matrix) {
    int result = 0;

    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            result += matrix[i][j] > 1 ? 1 : 0;
        }
    }

    return result;
}

int main() {
    ifstream infile("../input.txt");

    vector<array<int, 4>> lines = parse_lines(infile);
    array<array<int, 1000>, 1000> matrix = fill_matrix(lines);
    int result = count_greater_than_one_fields(matrix);

    cout << result << endl;

    return 0;
}
