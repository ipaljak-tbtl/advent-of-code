#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<sstream>

using namespace std;

vector<int> parse_bingo_numbers(ifstream &infile) {
    string bingo_numbers;
    vector<int> result;

    infile >> bingo_numbers;
    stringstream stream(bingo_numbers);

    while(stream.good()) {
        string substr;
        getline(stream, substr, ',');
        result.push_back(stoi(substr));
    }

    return result;
}

vector<array<array<int, 5>, 5>> parse_boards(ifstream &infile) {
    vector<array<array<int, 5>, 5>> boards{};

    for(int i = 0; i < 100; i++) {
        array<array<int, 5>, 5> board;
        for(int j = 0; j < 5; j++) {
            infile >> board[j][0] >> board[j][1] >> board[j][2] >> board[j][3] >> board[j][4];
        }
        boards.push_back(board);
    }

    return boards;
}

void check_board_numbers(vector<array<array<int, 5>, 5>> &boards, int bingo_number) {
    for(auto &board: boards) {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(board[i][j] == bingo_number) {
                    board[i][j] = -1;
                }
            }
        }
    }
}

int get_winner_index(vector<array<array<int, 5>, 5>> &boards) {
    int index = 0;
    for(auto &board: boards) {
        for(int i = 0; i < 5; i++) {
            if(board[i][0] + board[i][1] + board[i][2] + board[i][3] + board[i][4] == -5) return index;
        }

        for(int i = 0; i < 5; i++) {
            if(board[0][i] + board[1][i] + board[2][i] + board[3][i] + board[4][i] == -5) return index;
        }

        index++;
    }

    return -1;
}

int sum_unchecked_board_numbers(array<array<int, 5>, 5> &board) {
    int sum = 0;

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] != -1) {
                sum += board[i][j];
            }
        }
    }

    return sum;
}

int main() {
    ifstream infile("../input.txt");

    vector<int> bingo_numbers = parse_bingo_numbers(infile);
    vector<array<array<int, 5>, 5>> boards = parse_boards(infile);

    for(auto const& bingo_number: bingo_numbers) {
        check_board_numbers(boards, bingo_number);

        int winner_index;

        while((winner_index = get_winner_index(boards)) != -1) {
            int sum = sum_unchecked_board_numbers(boards[winner_index]);
            cout << bingo_number * sum << endl;
            boards.erase(boards.begin() + winner_index);
        }
    }

    return 0;
}
