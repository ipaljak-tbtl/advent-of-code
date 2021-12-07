#include <vector>
#include <fstream>
#include "board.h"

std::vector<int> load_random(std::ifstream& input);
std::vector<Board> load_tables(std::ifstream& input);
