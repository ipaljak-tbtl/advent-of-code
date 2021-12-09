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

int sum_low_points(vector<vector<int>> matrix) {
    int sum = 0;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            if(i - 1 >= 0 && j - 1 >= 0               && matrix[i][j] > matrix[i - 1][j - 1]) continue;
            if(i - 1 >= 0                             && matrix[i][j] > matrix[i - 1][j]    ) continue;
            if(i - 1 >= 0 && j + 1 < matrix[i].size() && matrix[i][j] > matrix[i - 1][j + 1]) continue;

            if(j - 1 >= 0               && matrix[i][j] > matrix[i][j - 1]) continue;
            if(j + 1 < matrix[i].size() && matrix[i][j] > matrix[i][j + 1]) continue;

            if(i + 1 < matrix.size() && j - 1 >= 0               && matrix[i][j] > matrix[i + 1][j - 1]) continue;
            if(i + 1 < matrix.size()                             && matrix[i][j] > matrix[i + 1][j]    ) continue;
            if(i + 1 < matrix.size() && j + 1 < matrix[i].size() && matrix[i][j] > matrix[i + 1][j + 1]) continue;

            sum += matrix[i][j] + 1;
        }
    }
    return sum;
}

int main() {
    auto matrix = parse_matrix();
    auto result = sum_low_points(matrix);

    cout << result << endl;

    return 0;
}
