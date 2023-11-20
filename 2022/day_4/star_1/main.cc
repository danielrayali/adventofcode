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

// Only test if inner_* is contained within outter_*
bool InRange(int outter_lower, int outter_higher, int inner_lower, int inner_higher) {
    if (inner_lower < outter_lower || inner_lower > outter_higher) {
        return false;
    }

    if (inner_higher < outter_lower || inner_higher > outter_higher) {
        return false;
    }

    return true;
}

bool HasAFullyContainedRange(const string& line) {
    vector<string> pairs = SplitString(line, ',');
    vector<string> left_range = SplitString(pairs[0], '-');
    int left_low = atoi(left_range[0].c_str());
    int left_high = atoi(left_range[1].c_str());

    vector<string> right_range = SplitString(pairs[1], '-');
    int right_low = atoi(right_range[0].c_str());
    int right_high = atoi(right_range[1].c_str());

    // Test left outter
    if (InRange(left_low, left_high, right_low, right_high)) {
        return true;
    }

    // Test right outter
    if (InRange(right_low, right_high, left_low, left_high)) {
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
        if (HasAFullyContainedRange(line)) {
            occurances += 1;
        }
    }

    cout << "Occurances: " << occurances << endl;

    return 0;
}
