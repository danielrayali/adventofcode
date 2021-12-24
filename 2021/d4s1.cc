#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> Split(string& input) {
    vector<string> values;
    ssize_t prev = 0, cur = 0;
    for (int i = 0; i < 5; ++i) {
        cur = input.find_first_of(' ', prev);
        if (cur != std::string::npos) {
            values.push_back(input.substr(cur, (cur - prev)));
        } else {
            values.push_back(input.substr(cur));
        }
        prev = cur;
    }
    return values;
}
class BingoBoard {
public:
    BingoBoard(std::ifstream& input) {
        string line;
        for (int i = 0; i < 5; ++i) {
            getline(input, line);
            vector<string> values = Split(line);
            board_.push_back({});
            for (auto value : values) {
                board_.back().push_back(atoi(value.c_str()));
            }
        }
    }

    void Print() {
        for (auto line : board_) {
            for (auto value : line) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

private:
    vector<vector<int>> board_;
};

int main(int argc, char* argv[]) {
    ifstream input("d4s1.txt");
    BingoBoard bingo_board(input);
    bingo_board.Print();
    return 0;
}