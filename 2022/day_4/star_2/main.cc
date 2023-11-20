#include <iostream>
#include <fstream>
#include <vector>

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

// Tests whether right overlaps left
bool HasOverlap(int left_lower, int left_higher, int right_lower, int right_higher) {
    if (right_lower >= left_lower && right_lower <= left_higher) {
        return true;
    }

    if (right_higher >= left_lower && right_higher <= left_higher) {
        return true;
    }

    return false;
}

bool HasAnyOverlap(const string& line) {
    vector<string> pairs = SplitString(line, ',');
    vector<string> left_range = SplitString(pairs[0], '-');
    int left_low = atoi(left_range[0].c_str());
    int left_high = atoi(left_range[1].c_str());

    vector<string> right_range = SplitString(pairs[1], '-');
    int right_low = atoi(right_range[0].c_str());
    int right_high = atoi(right_range[1].c_str());

    if (HasOverlap(left_low, left_high, right_low, right_high)) {
        return true;
    }

    if (HasOverlap(right_low, right_high, left_low, left_high)) {
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    int occurances = 0;
    while (getline(input, line)) {
        if (HasAnyOverlap(line)) {
            occurances += 1;
        }
    }

    cout << "Occurances: " << occurances << endl;

    return 0;
}
