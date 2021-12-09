#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>

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


bool is_lowest_condition(vector<vector<int>> matrix, int i, int j) {
    if(i - 1 >= 0 && j - 1 >= 0               && matrix[i][j] > matrix[i - 1][j - 1]) return false;
    if(i - 1 >= 0                             && matrix[i][j] > matrix[i - 1][j]    ) return false;
    if(i - 1 >= 0 && j + 1 < matrix[i].size() && matrix[i][j] > matrix[i - 1][j + 1]) return false;

    if(j - 1 >= 0               && matrix[i][j] > matrix[i][j - 1]) return false;
    if(j + 1 < matrix[i].size() && matrix[i][j] > matrix[i][j + 1]) return false;

    if(i + 1 < matrix.size() && j - 1 >= 0               && matrix[i][j] > matrix[i + 1][j - 1]) return false;
    if(i + 1 < matrix.size()                             && matrix[i][j] > matrix[i + 1][j]    ) return false;
    if(i + 1 < matrix.size() && j + 1 < matrix[i].size() && matrix[i][j] > matrix[i + 1][j + 1]) return false;

    return true;
}

int bfs_size(set<pair<int, int>>& seen, vector<vector<int>> const& matrix, int i, int j) {
    if(seen.find(make_pair(i, j)) != seen.end()) return 0;

    seen.insert(make_pair(i, j));

    int result = 1;

    if(i - 1 >= 0               && matrix[i - 1][j] != 9) result += bfs_size(seen, matrix, i-1, j);
    if(j - 1 >= 0               && matrix[i][j - 1] != 9) result += bfs_size(seen, matrix, i, j-1);
    if(i + 1 < matrix.size()    && matrix[i + 1][j] != 9) result += bfs_size(seen, matrix, i+1, j);
    if(j + 1 < matrix[0].size() && matrix[i][j + 1] != 9) result += bfs_size(seen, matrix, i, j+1);

    return result;
}

int calculate_three_biggest_sizes(vector<vector<int>> matrix) {
    vector<int> sizes;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            if(is_lowest_condition(matrix, i, j)) {
                set<pair<int, int>> seen;
                sizes.push_back(bfs_size(seen, matrix, i, j));
            }
        }
    }

    sort(sizes.begin(), sizes.end());
    int l = sizes.size();

    return sizes[l - 1] * sizes[l - 2] * sizes[l - 3];
}

int main() {
    auto matrix = parse_matrix();
    auto result = calculate_three_biggest_sizes(matrix);

    cout << result << endl;

    return 0;
}
