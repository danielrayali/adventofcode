#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <sstream>
#include <vector>

using namespace std;

// AI generated!
vector<string> SplitString(const string& str, char delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

struct Position {
    int x = 0; 
    int y = 0;

    bool operator==(const Position& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
};

void ProcessTailMove(Position& head, Position& tail) {
    // Determine if a tail move is needed
    const int x_diff = head.x - tail.x;
    const int y_diff = head.y - tail.y;
    if (abs(x_diff) < 2 && abs(y_diff) < 2) {
        return;
    }

    // Determine if it will move diagonal or not
    if (abs(x_diff) > 0 && abs(y_diff) > 0) {
        // Process diagonal move. Determine quadrant and apply
        if (x_diff > 0 && y_diff > 0) {
            tail.x++; tail.y++;
        } else if (x_diff > 0 && y_diff < 0) {
            tail.x++; tail.y--;
        } else if (x_diff < 0 && y_diff > 0) {
            tail.x--; tail.y++;
        } else if (x_diff < 0 && y_diff < 0) {
            tail.x--; tail.y--;
        }
    } else {
        // Process non-diagonal move
        if (x_diff > 1) {
            tail.x++;
        } else if (x_diff < -1) {
            tail.x--;
        } else if (y_diff > 1) {
            tail.y++;
        } else if (y_diff < -1) {
            tail.y--;
        }
    }
}

void ProcessMove(const string& line, Position& head, Position& tail, vector<Position>& tail_positions) {
    const vector<string> line_split = SplitString(line, ' ');
    if (line_split.size() != 2 || line_split.at(0).size() != 1) {
        throw runtime_error("Invalid command");
    }

    const char direction = line_split[0].at(0);
    int spaces = atoi(line_split[1].c_str());

    while (spaces > 0) {
        switch (direction) {
        case 'U': head.y++; break;
        case 'D': head.y--; break;
        case 'L': head.x--; break;
        case 'R': head.x++; break;
        default:
            throw runtime_error("Invalid direction detected");
        }

        ProcessTailMove(head, tail);

        // Using a set<> with a proper opertor<() function would replace this slow code.
        bool contains = false;
        for (const auto& pos : tail_positions) {
            if (pos == tail) {
                contains = true;
            }
        }

        if (!contains) {
            tail_positions.push_back(tail);
        }

        spaces--;
    }
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    Position head, tail;
    vector<Position> tail_positions;
    while (getline(input, line)) {
        ProcessMove(line, head, tail, tail_positions);
    }

    cout << "The number of unique positions the tail visited is: " << tail_positions.size() << endl;

    return 0;
}
