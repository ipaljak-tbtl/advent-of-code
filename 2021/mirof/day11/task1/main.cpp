#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>

using namespace std;

vector<vector<int>> parse_matrix() {
    ifstream infile("../input.txt");
    string numbers;
    vector<vector<int>> matrix{};

    while(infile >> numbers) {
        vector<int> row{};
        for(int i = 0; i < numbers.size(); i++) {
            row.push_back(numbers[i] - '0');
        }
        matrix.push_back(row);
    }

    return matrix;
}

void flash(vector<vector<int>>& matrix, int i, int j) {
    if(i - 1 >= 0 && j - 1 >= 0               && matrix[i-1][j-1] != 0) matrix[i-1][j-1]++;
    if(i - 1 >= 0                             && matrix[i-1][j] != 0) matrix[i-1][j]++    ;
    if(i - 1 >= 0 && j + 1 < matrix[i].size() && matrix[i-1][j+1] != 0) matrix[i-1][j+1]++;

    if(j - 1 >= 0               && matrix[i][j - 1] != 0) matrix[i][j - 1]++;
    if(j + 1 < matrix[i].size() && matrix[i][j + 1] != 0) matrix[i][j + 1]++;

    if(i + 1 < matrix.size() && j - 1 >= 0               && matrix[i + 1][j - 1] != 0) matrix[i + 1][j - 1]++;
    if(i + 1 < matrix.size()                             && matrix[i + 1][j]     != 0) matrix[i + 1][j]++    ;
    if(i + 1 < matrix.size() && j + 1 < matrix[i].size() && matrix[i + 1][j + 1] != 0) matrix[i + 1][j + 1]++;

    matrix[i][j] = 0;
}

int simulate(vector<vector<int>> matrix, int days) {
    int flashes = 0;
    while(days--) {
        for(vector<int>& row: matrix) for(int& elem: row) elem++;

        auto save_matrix = matrix;

        while(true) {
            for(int i = 0; i < matrix.size(); i++) {
                for(int j = 0; j < matrix[0].size(); j++) {
                    if(matrix[i][j] >= 10) {
                        flash(matrix, i, j);
                        flashes++;
                    }
                }
            }

            if(save_matrix == matrix) break;
            save_matrix = matrix;
        }
    }

    for(vector<int>& row: matrix) {
        for(int& elem: row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    return flashes;
}

int main() {
    int days = 100;

    auto matrix = parse_matrix();
    auto result = simulate(matrix, days);

    cout << result << endl;

    return 0;
}
