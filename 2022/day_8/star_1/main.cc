#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool IsVisible(const int start_i, const int start_j, const vector<vector<char>>& grid) {
    // Check if visible from the top
    const char height = grid[start_i][start_j];
    bool is_visible = true;
    for (int i = 0; i < start_i; i++) {
        if (grid[i][start_j] >= height) {
            is_visible = false;
            break;
        }
    }

    if (is_visible) {
        return true;
    }

    // Check if visible from the bottom
    is_visible = true;
    for (int i = start_i + 1; i < grid.size(); i++) {
        if (grid[i][start_j] >= height) {
            is_visible = false;
            break;
        }
    }

    if (is_visible) {
        return true;
    }

    // Check if visible from the left 
    is_visible = true;
    for (int j = 0; j < start_j; j++) {
        if (grid[start_i][j] >= height) {
            is_visible = false;
            break;
        }
    }
    
    if (is_visible) {
        return true;
    }

    // Check if visible from the right
    is_visible = true;
    for (int j = start_j + 1; j < grid.at(0).size(); j++) {
        if (grid[start_i][j] >= height) {
            is_visible = false;
            break;
        }
    }
    
    return is_visible;
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    vector<vector<char>> grid;
    while (getline(input, line)) {
        grid.push_back({});
        for (auto letter : line) {
            grid.back().push_back(letter);
        }
    }

    if (grid.size() == 0) {
        throw runtime_error("Error populating grid");
    }

    // Calculate all trees on the outter edge. Minus 4 to avoid double-counting the corners
    int total_visible = grid.size() * 2 + (grid.at(0).size() * 2 - 4);

    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid.at(0).size() - 1; j++) {
            if (IsVisible(i, j, grid)) {
                total_visible++;
            }
        }
    }

    cout << "The total number of visible trees is: " << total_visible << endl;

    return 0;
}