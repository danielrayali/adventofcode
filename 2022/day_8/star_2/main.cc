#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int CalculateScenicScore(const int start_i, const int start_j, const vector<vector<char>>& grid) {
    // Count visible from the top
    const char height = grid[start_i][start_j];
    int scores[4] = { 0 };
    for (int i = start_i - 1; i >= 0; i--) {
        scores[0]++;
        if (grid[i][start_j] >= height) {
            break;
        }
    }

    // Count visible from the bottom
    for (int i = start_i + 1; i < grid.size(); i++) {
        scores[1]++;
        if (grid[i][start_j] >= height) {
            break;
        }
    }

    // Count visible from the left 
    for (int j = start_j - 1; j >= 0; j--) {
        scores[2]++;
        if (grid[start_i][j] >= height) {
            break;
        }
    }
    
    // Count visible from the right
    for (int j = start_j + 1; j < grid.at(0).size(); j++) {
        scores[3]++;
        if (grid[start_i][j] >= height) {
            break;
        }
    }
    
    return (scores[0] * scores[1] * scores[2] * scores[3]);
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

    int max_scenic_score = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.at(0).size(); j++) {
            int scenic_score = CalculateScenicScore(i, j, grid);
            if (scenic_score > max_scenic_score) {
                max_scenic_score = scenic_score;
            }
        }
    }

    cout << "The maximum scenic score is: " << max_scenic_score << endl;

    return 0;
}