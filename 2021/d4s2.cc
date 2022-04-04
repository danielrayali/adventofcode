#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

vector<string> Split(const string& input, char delim) {
    vector<string> values;
    size_t start = 0, end = 0;
    while (start < input.size()) {
        while ((start < input.size()) && (input.at(start) == delim)) {
            start++;
        }

        if (start >= input.size()) {
            break;
        }

        end = start + 1;
        while ((end < input.size()) && (input.at(end) != delim)) {
            end++;
        }

        values.emplace_back(input.substr(start, (end - start)));
        start = end + 1;
    }
    return values;
}

class BingoBoard {
public:
    BingoBoard(const vector<vector<int>>& values) {
        board_ = values;
        marks_ = values;
        has_bingo_ = false;
    }

    bool HasBingo() const {
        return has_bingo_;
    }

    // Mark the value and return true if the board is a winner
    bool MarkAndCheck(const int value) {
        this->Mark(value);
        return this->Check();
    }

    void Print() {
        for (auto line : board_) {
            for (auto value : line) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    void PrintMarks() {
        for (auto line : marks_) {
            for (auto value : line) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    int SumUnmarked() const {
        int sum = 0;
        for (auto row : marks_) {
            for (auto value : row) {
                if (value > 0) {
                    sum += value;
                }
            }
        }
        return sum;
    }

private:
    vector<vector<int>> board_;
    vector<vector<int>> marks_;
    mutable bool has_bingo_ = false;

    void Mark(const int value) {
        for (auto& row : marks_) {
            for (auto& entry : row) {
                if (entry == value) {
                    entry = -1;
                }
            }
        }
    }

    bool Check() const {
        // Check rows
        for (size_t i = 0; i < marks_.size(); ++i) {
            if (this->CheckRow(i)) {
                return (has_bingo_ = true);
            }
        }

        // Check columns
        for (size_t i = 0; i < marks_.at(0).size(); ++i) {
            if (this->CheckColumn(i)) {
                return (has_bingo_ = true);
            }
        }

        return false;
    }

    bool CheckColumn(const size_t column) const {
        for (size_t i = 0; i < marks_.size(); ++i) {
            if (marks_.at(i).at(column) != -1) {
                return false;
            }
        }
        return true;
    }

    bool CheckRow(const size_t row) const {
        for (auto value : marks_[row]) {
            if (value != -1) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    ifstream input("d4s1.txt");
    string marks_line;
    getline(input, marks_line);
    vector<string> value_strs = Split(marks_line, ',');
    vector<int> marks;
    for (auto value : value_strs) {
        marks.push_back(atoi(value.c_str()));
        cout << value << " ";
    }
    cout << endl;

    int temp;
    vector<BingoBoard> bingo_boards;
    while (!input.eof()) {
        vector<vector<int>> matrix;
        for (int i = 0; i < 5; ++i) {
            matrix.push_back({});
            for (int j = 0; j < 5; ++j) {
                input >> temp;
                matrix.back().push_back(temp);
            }
        }
        bingo_boards.emplace_back(matrix);
        bingo_boards.back().Print();
        cout << "--" << endl;
    }

    bool bingo = false;
    int count = 0;
    for (auto value : marks) {
        cout << "Mark: " << value << endl;
        for (int i = 0; i < bingo_boards.size(); ++i) {
            if (bingo_boards[i].HasBingo()) {
                continue;
            }
            if (bingo_boards[i].MarkAndCheck(value)) {
                count++;
                cout << "A board found bingo: " << bingo_boards[i].HasBingo() << endl;
                if (count == bingo_boards.size()) {
                    cout << "The last board's bingo was found: " << i << endl;
                    cout << "Marked " << value << endl;
                    bingo_boards[i].PrintMarks();
                    cout << "Sum of unmarked values: " << bingo_boards[i].SumUnmarked() << endl;
                    cout << "Product of the sum and the last marked value: " << bingo_boards[i].SumUnmarked() * value << endl;
                    bingo = true;
                    break;
                }
            }
        }
        if (bingo) {
            break;
        }
    }

    return 0;
}
