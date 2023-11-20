#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

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

// Possible inputs:
// "[T]     [Q]             [S] "
// "[D] [V] [V]             [Q] [N] [C]"
// "[P] [G] [R] [Z] [Z] [C] [Z] [G] [P]"
void ParseStackLine(const string& line, vector<stack<char>>& stacks) {
    // Make sure we have enough stacks
    while (stacks.size() < ((line.size() + 1) / 4)) {
        stacks.push_back({});
    }

    size_t line_index = 1;
    size_t stacks_index = 0;
    while (line_index < line.size()) {
        if (line.at(line_index) != ' ') {
            stacks[stacks_index].emplace(line.at(line_index));
        }
        line_index += 4;
        stacks_index++;
    }
}

void ProcessMoveCommand(const string& command, vector<stack<char>>& stacks) {
    vector<string> results = SplitString(command, ' ');
    const int num_to_move = atoi(results[1].c_str());
    const int source = atoi(results[3].c_str()) - 1;
    const int dest = atoi(results[5].c_str()) - 1;

    stack<char> buffer;
    for (int i = 0; i < num_to_move; ++i) {
        buffer.emplace(stacks.at(source).top());
        stacks.at(source).pop();
    }

    while (!buffer.empty()) {
        stacks.at(dest).emplace(buffer.top());
        buffer.pop();
    }
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    // Read lines in order from the file, but store them in a stack.
    // Well process lines by popping them off the stack to reverse the order.
    // This will allow our in-memory stacks to be populated in the correct order.
    // WARNING: This means we store the entire file in memory. A better approach
    // would probably be to memory map it and read lines "up" towards offset 0.
    stack<string> lines;
    string line;
    vector<stack<char>> stacks;
    getline(input, line);
    while (line.substr(0, 10) != " 1   2   3") {
        lines.emplace(line);
        getline(input, line);
    }

    while (!lines.empty()) {
        ParseStackLine(lines.top(), stacks);
        lines.pop();
    }

    // Skip separator
    getline(input, line);

    // Process move commmands
    while (getline(input, line)) {
        ProcessMoveCommand(line, stacks);
    }

    // Print results
    for (auto iter : stacks) {
        cout << iter.top();
    }
    cout << endl;

    return 0;
}
