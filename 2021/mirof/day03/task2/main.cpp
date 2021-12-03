#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main() {
    std::ifstream infile("../input.txt");

    int line_length = 12; // 12
    int file_length = 1000; // 1000
    bool input[file_length][line_length] = {false};
    bool flags1[file_length] = {false};
    bool flags2[file_length] = {false};

    char character;

    int i = 0, j = 0;
    while(infile.get(character)) {
        if(character == '\n') { i++; j = 0; continue; }

        input[i][j] = character == '1';
        j++;
    }

    for(i = 0; i < line_length; i++) {
        int counter = 0;
        int left_elements = 0;
        for(j = 0; j < file_length; j++) {
            if(flags1[j]) continue;
            counter += input[j][i];
            left_elements++;
        }

        bool leave_ones = counter >= (int ((left_elements + 1) / 2));

        for(j = 0; j < file_length; j++) {
            if(flags1[j]) continue;

            if(leave_ones && input[j][i] == 0) flags1[j] = true;
            if(!leave_ones && input[j][i] == 1) flags1[j] = true;
        }
    }

    int result1 = 0;
    for(j = 0; j < file_length; j++) {
        if(!flags1[j]) {
            for(int i = 0; i < line_length; i++) {
                bool decimal = input[j][i];
                result1 |= decimal << (line_length - i - 1);
            }
        }
    }

    for(i = 0; i < line_length; i++) {
        int exit = 0;
        for(j = 0; j < file_length; j++) {
            exit += !flags2[j];
        }
        if(exit == 1) break;

        int counter = 0;
        int left_elements = 0;
        for(j = 0; j < file_length; j++) {
            if(flags2[j]) continue;
            counter += !input[j][i];
            left_elements++;
        }

        bool leave_zeros = counter <= (int ((left_elements) / 2));

        for(j = 0; j < file_length; j++) {
            if(flags2[j]) continue;

            if(leave_zeros && input[j][i] == 1) flags2[j] = true;
            if(!leave_zeros && input[j][i] == 0) flags2[j] = true;
        }
    }

    int result2 = 0;
    for(j = 0; j < file_length; j++) {
        if(!flags2[j]) {
            for(int i = 0; i < line_length; i++) {
                bool decimal = input[j][i];
                result2 |= decimal << (line_length - i - 1);
            }
        }
    }

    cout << result1 * result2 << endl;

    return 0;
}
